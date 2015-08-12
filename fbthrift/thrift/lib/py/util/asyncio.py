# @lint-avoid-pyflakes2
# @lint-avoid-python-3-compatibility-imports

import sys
import asyncio

from thrift.Thrift import TMessageType, TApplicationException, TType
import thrift.server.TAsyncioServer as TAsyncioServer

def process_main(func):
    """Decorator for process method."""

    def nested(self, iprot, oprot, server_ctx=None):
        name, _, seqid = iprot.readMessageBegin()
        if isinstance(name, bytes):
            name = name.decode('utf8')
        if name not in self._processMap:
            iprot.skip(TType.STRUCT)
            iprot.readMessageEnd()
            x = TApplicationException(
                TApplicationException.UNKNOWN_METHOD,
                'Unknown function {!r}'.format(name),
            )
            oprot.writeMessageBegin(name, TMessageType.EXCEPTION, seqid)
            x.write(oprot)
            oprot.writeMessageEnd()
            oprot.trans.flush()
        else:
            yield from self._processMap[name](
                self, seqid, iprot, oprot, server_ctx,
            )
    return nested


def process_method(oneway=False):
    """Decorator for process_xxx methods for asyncio."""
    def _decorator(func):
        def nested(self, seqid, iprot, oprot, server_ctx):
            fn_name = func.__name__.split('_', 1)[-1]
            handler_ctx = self._event_handler.getHandlerContext(
                fn_name, server_ctx,
            )
            args = getattr(sys.modules[func.__module__], fn_name + "_args")()
            reply_type = TMessageType.REPLY
            self._event_handler.preRead(handler_ctx, fn_name, args)
            args.read(iprot)
            iprot.readMessageEnd()
            self._event_handler.postRead(handler_ctx, fn_name, args)

            result = yield from func(self, args, handler_ctx)
            if not oneway:
                if isinstance(result, TApplicationException):
                    reply_type = TMessageType.EXCEPTION
                self._event_handler.preWrite(handler_ctx, fn_name, result)
                oprot.writeMessageBegin(fn_name, reply_type, seqid)
                result.write(oprot)
                oprot.writeMessageEnd()
                oprot.trans.flush()
                self._event_handler.postWrite(handler_ctx, fn_name, result)
        return nested
    return _decorator


def run_on_thread(func):
    func._run_on_thread = True
    return func


def should_run_on_thread(func):
    return getattr(func, "_run_on_thread", False)


@asyncio.coroutine
def create_client(client_klass, *, host=None, port=None, loop=None):
    """
    create a asyncio thrift client and return it
    This is a coroutine
    :param client_klass: thrift Client class
    :param host: hostname/ip, None = loopback
    :param port: port number
    :param loop: asyncio event loop
    """
    if not loop:
        loop = asyncio.get_event_loop()
    transport, protocol = yield from loop.create_connection(
        TAsyncioServer.ThriftClientProtocolFactory(client_klass),
        host=host, port=port)
    return protocol.client
