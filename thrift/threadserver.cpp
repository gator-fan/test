/*************************************************************************
 * @File Name: threadserver.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月29日 星期三 17时48分24秒
 ************************************************************************/


#include <iostream>
#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>
#include <server/TThreadPoolServer.h>
#include <server/TThreadedServer.h>
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TTransportUtils.h>
#include "gen-cpp/Test.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace ::apache::thrift::concurrency;
using namespace uctest;

using boost::shared_ptr;

class TestHandler : virtual public TestIf {
  public:
    TestHandler() {
      // Your initialization goes here
    }

    void pingpong(std::string& _return, const std::string& data) {
      // Your implementation goes here
      printf("pingpong\n");
    }
};

/*
int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<SomethingHandler> handler(new SomethingHandler());
  shared_ptr<TProcessor> processor(new SomethingProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
*/


int main(int argc, char **argv) {
  shared_ptr<TestHandler> handler(new TestHandler());
  shared_ptr<TProcessor> processor(new TestProcessor(handler));
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(9090));

  shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(5);
  shared_ptr<PosixThreadFactory> threadFactory
    = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());

  threadManager->threadFactory(threadFactory);
  threadManager->start();
  printf("start.../n");

  TThreadPoolServer server(processor,
      serverTransport,
      transportFactory,
      protocolFactory,
      threadManager);

  server.serve();

  printf("end/n");
  return 0;
}
