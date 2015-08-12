"""
PyRemote

Used by PyRemote files generated by
  /thrift/compiler/generate/t_py_generator.cc

Remote.run is the interface used by the generated code.
Based on whether --host or --url is specified as a commandline option,
either a RemoteHostClient or RemoteHttpClient is instantiated to
handle the request.

Additional remote client types (subclasses of RemoteClient) can be
registered with the Remote class to define different ways of specifying a
host or communicating with the host. When registering a new client type,
you can specify the option used to select that type (i.e., url) with the
selector_option attribute, and you can specify additional commandline options
with the options attribute. See the implementations of RemoteHostClient
and RemoteHttpClient for examples.
"""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import itertools
import optparse
import os
import pprint
from six.moves.urllib.parse import urlparse
from six import string_types
import sys
import traceback

from thrift import Thrift
from thrift.transport import TTransport, TSocket, TSSLSocket, THttpClient
from thrift.protocol import TBinaryProtocol, TCompactProtocol, \
    TJSONProtocol, THeaderProtocol

class Function(object):
    """Metadata for a service method"""
    def __init__(self, name, return_type, args):
        self.name = name
        self.return_type = return_type
        self.args = args

class RemoteClient(object):
    usage = '%prog [OPTIONS] FUNCTION [ARGS ...]'

    def __init__(self, functions, service_class, ttypes, op, default_port):
        self.functions = functions
        self.service_class = service_class
        self.ttypes = ttypes
        self.op = op  # OptionParser
        self.default_port = default_port

    def _print_functions(self, out):
        """Print all the functions available from this service"""
        out.write('Functions:\n')
        for fn_name in sorted(self.functions):
            fn = self.functions[fn_name]
            if fn.return_type is None:
                out.write('  oneway void ')
            else:
                out.write('  %s ' % (fn.return_type,))
            out.write(fn_name + '(')
            out.write(', '.join('%s %s' % (type, name)
                                for type, name, true_type in fn.args))
            out.write(')\n')

    def _exit(self, error_message=None, status=os.EX_USAGE, err_out=sys.stderr):
        """ Report an error, show help information, and exit the program """
        if error_message is not None:
            print("Error: %s" % error_message, file=err_out)

        if status is os.EX_USAGE:
            # Print usage info
            if self.op is not None:
                self.op.print_help(err_out)

        elif status is os.EX_CONFIG:
            if self.functions is not None:
                self._print_functions(err_out)

        sys.exit(status)

    def _validate_options(self, options):
        """Check option validity and call _exit if there is an error"""
        pass

    def _get_client(self, options):
        """Get the thrift client that will be used to make method calls"""
        raise TypeError("_get_client should be called on "
                        "a subclass of RemoteClient")

    def _close_client(self):
        """After making the method call, do any cleanup work"""
        pass

    def _eval_arg(self, arg, thrift_types):
        """Evaluate a commandline argument within the scope of the IF types"""
        locals().update(thrift_types)
        return eval(arg)

    def _process_fn_args(self, fn, args):
        """Proccess positional commandline args as function arguments"""
        if len(args) != len(fn.args):
            self._exit(error_message=('"%s" expects %d arguments '
                       '(received %d)') % (fn.name, len(fn.args), len(args)))

        # Get all custom Thrift types
        thrift_types = {}
        for key in dir(self.ttypes):
            thrift_types[key] = getattr(self.ttypes, key)

        fn_args = []
        for arg, arg_info in itertools.izip(args, fn.args):
            if arg_info[2] == 'string':
                # For ease-of-use, we don't eval string arguments, simply so
                # users don't have to wrap the arguments in quotes
                fn_args.append(arg)
                continue
            try:
                value = self._eval_arg(arg, thrift_types)
            except:
                traceback.print_exc(file=sys.stderr)
                self._exit(error_message='error parsing argument "%s"' % (arg,),
                           status=os.EX_DATAERR)
            fn_args.append(value)

        return fn_args

    def _process_args(self, args, options):
        """Populate instance data using commandline arguments"""
        if len(args) < 1:
            self._exit()
        fn_name = args[0]
        if fn_name not in self.functions:
            self._exit(error_message='Unknown function "%s"' % fn_name,
                       status=os.EX_CONFIG)
        else:
            function = self.functions[fn_name]

        function_args = self._process_fn_args(function, args[1:])

        self._validate_options(options)
        return function.name, function_args

    def _execute(self, fn_name, fn_args, options):
        """Make the requested call.
        Assumes _parse_args() and _process_args() have already been called.
        """
        client = self._get_client(options)

        # Call the function
        method = getattr(client, fn_name)
        try:
            ret = method(*fn_args)
        except Thrift.TException as e:
            ret = 'Exception:\n' + str(e)

        if isinstance(ret, string_types):
            print(ret)
        else:
            pprint.pprint(ret, indent=2)

        self._close_client()

    def run(self, args, options):
        fn_name, fn_args = self._process_args(args, options)
        self._execute(fn_name, fn_args, options)
        self._exit(status=0)

class RemoteTransportClient(RemoteClient):
    """Abstract class for clients with transport manually opened and closed"""
    options = [
        (
            ['f', 'framed'],
            {
                'action': 'store_true',
                'default': False,
                'help': 'Use framed transport'
            }
        ), (
            ['s', 'ssl'],
            {
                'action': 'store_true',
                'default': False,
                'help': 'Use SSL socket'
            }
        ), (
            ['U', 'unframed'],
            {
                'action': 'store_true',
                'default': False,
                'help': 'Use unframed transport'
            }
        ), (
            ['j', 'json'],
            {
                'action': 'store_true',
                'default': False,
                'help': 'Use TJSONProtocol'
            }
        ), (
            ['c', 'compact'],
            {
                'action': 'store_true',
                'default': False,
                'help': 'Use TCompactProtocol'
            }
        )
    ]

    def _get_client_by_transport(self, options, transport, socket=None):
        # Create the protocol and client
        if options.json:
            protocol = TJSONProtocol.TJSONProtocol(transport)
        elif options.compact:
            protocol = TCompactProtocol.TCompactProtocol(transport)

        # No explicit option about protocol is specified. Try to infer.
        elif options.framed or options.unframed:
            protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        else:
            if socket is None:
                self._exit(error_message=('No valid protocol '
                                          'specified for %s' % (type(self))),
                           status=os.EX_USAGE)
            else:
                protocol = THeaderProtocol.THeaderProtocol(socket)
                transport = protocol.trans
        transport.open()
        self._transport = transport

        client = self.service_class.Client(protocol)
        return client

    def close_client(self):
        self._transport.close()

    def _validate_options(self, options):
        super(RemoteTransportClient, self)._validate_options(options)
        if options.framed and options.unframed:
            self._exit(error_message='cannot specify both '
                       '--framed and --unframed')

    def _parse_host_port(self, value, default_port):
        parts = value.rsplit(':', 1)
        if len(parts) == 1:
            return (parts[0], default_port)
        try:
            port = int(parts[1])
        except ValueError:
            raise ValueError('invalid port: ' + parts[1])
        return (parts[0], port)

class RemoteHostClient(RemoteTransportClient):
    selector_option = 'host'
    options = list(RemoteTransportClient.options)
    options.append((
        ['h', 'host'],
        {
            'action': 'store',
            'metavar': 'HOST[:PORT]',
            'help': 'The host and port to connect to'
        }
    ))

    def _get_client(self, options):
        host, port = self._parse_host_port(options.host, self.default_port)
        socket = (TSSLSocket.TSSLSocket(host, port) if options.ssl
                  else TSocket.TSocket(host, port))
        if options.framed:
            transport = TTransport.TFramedTransport(socket)
        else:
            transport = TTransport.TBufferedTransport(socket)
        return self._get_client_by_transport(options, transport, socket=socket)

class RemoteHttpClient(RemoteTransportClient):
    selector_option = 'url'
    options = list(RemoteTransportClient.options)
    options.append((
        ['u', 'url'],
        {
            'action': 'store',
            'help': 'The URL to connect to, for HTTP transport'
        }
    ))

    def _get_client(self, options):
        url = urlparse(options.url)
        host, port = self._parse_host_port(url[1], 80)
        transport = THttpClient.THttpClient(options.url)
        return self._get_client_by_transport(options, transport)

    def _validate_options(self, options):
        """Check if there are any option inconsistencies, and exit if so"""
        super(RemoteHttpClient, self)._validate_options(options)
        if not any([options.unframed, options.json]):
            self._exit(error_message='can only specify --url with '
                       '--unframed or --json')

class Remote(object):
    _client_types = []

    @classmethod
    def register_client_type(cls, client_type):
        if not issubclass(client_type, RemoteClient):
            raise TypeError(('Remote client must be of type RemoteClient. '
                             'Got type %s.' % client_type.__name__))
        if client_type is RemoteClient:
            raise TypeError(('Remote client must be a strict subclass '
                             'of RemoteClient.'))
        if not hasattr(client_type, 'selector_option'):
            raise AttributeError(('Remote client must have a '
                                  'selector_option field.'))

        if client_type not in cls._client_types:
            cls._client_types.append(client_type)

    @classmethod
    def _get_all_options(cls):
        all_options = {}
        for client_type in cls._client_types:
            for option in client_type.options:
                (short_flag, long_flag), _ = option
                # Check if we have conflicting options
                if short_flag in all_options:
                    (_, old_long_flag), _ = all_options[short_flag]
                    if old_long_flag != long_flag:
                        sys.stderr.write(('Conflicting options: (-%s, --%s), '
                                          '(-%s, --%s)\n') % (
                                              short_flag, old_long_flag,
                                              short_flag, long_flag))
                        sys.exit(os.EX_DATAERR)
                else:
                    all_options[short_flag] = option
        return all_options.values()

    @classmethod
    def _parse_options(cls, all_options, argv):
        op = optparse.OptionParser(usage=RemoteClient.usage,
                                   add_help_option=False)
        op.disable_interspersed_args()

        op.add_option('-?', '--help',
                      action='help',
                      help='Show this help message and exit')

        for (short_flag, long_flag), kwargs in all_options:
            op.add_option('-%s' % short_flag, '--%s' % long_flag, **kwargs)

        options, args = op.parse_args(argv[1:])
        return (op, options, args)

    @classmethod
    def _get_client_type(cls, options, op):
        matching_types = [ct for ct in cls._client_types if
                          getattr(options, ct.selector_option) is not None]
        if len(matching_types) != 1:
            sys.stderr.write('Must specify exactly one of [%s]\n' % (
                ', '.join('--%s' % ct.selector_option
                          for ct in cls._client_types)))
            op.print_help(sys.stderr)
            sys.exit(os.EX_USAGE)
        else:
            return matching_types[0]

    @classmethod
    def run(cls, functions, service_class, ttypes, argv, default_port=9090):
        all_options = cls._get_all_options()
        op, options, args = cls._parse_options(all_options, argv)
        client_type = cls._get_client_type(options, op)
        client = client_type(functions, service_class, ttypes, op, default_port)
        client.run(args, options)

Remote.register_client_type(RemoteHostClient)
Remote.register_client_type(RemoteHttpClient)
