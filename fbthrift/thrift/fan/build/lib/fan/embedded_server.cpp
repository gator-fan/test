#include <iostream>
#include "gen-cpp2/Calculator.h"
#include <thrift/lib/cpp2/server/ThriftServer.h>

using namespace std;
using namespace apache::thrift;
using namespace example::cpp2;

class CalculatorSvc : public CalculatorSvIf
{
  public:
    virtual ~CalculatorSvc() {}
    void async_tm_add(
        std::unique_ptr<apache::thrift::HandlerCallback<int64_t>> callback,
        int32_t num1,
        int32_t num2)
    {
      cout << "Got async request " << num1 << " + " << num2 << endl;
      callback->result(num1 + num2);
    }
};

// httpHandler is called whenever a http request is received by thrift server
void httpHandler(
    apache::thrift::async::TEventBase* ev,
    std::shared_ptr<apache::thrift::async::TAsyncTransport> tr,
    std::unique_ptr<folly::IOBuf> buf)
{
  /*
buf: contains the request header raw data. To get the request detail
you must use some http request header parser.

The response has to be written in tr. This is basically a socket.
*/
  std::cout << "Got http request" << std::endl;
  // Create http response. A better approach will be to use some http response builder
  // But for this example, we are directly preparing raw response
  std::string resp = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 11\r\n\r\nHello World";
  tr->write(nullptr, resp.c_str(), resp.size());
}

int main(int argc, char **argv) {
  ThriftServer* s = new ThriftServer();
  getHandlerFunc hf = httpHandler;
  // Set http handler
  s->setGetHandler(hf);
  std::shared_ptr<CalculatorSvc> ptr(new  CalculatorSvc());
  s->setInterface(ptr);
  s->setPort(9090);
  s->serve();
  return 0;
}
