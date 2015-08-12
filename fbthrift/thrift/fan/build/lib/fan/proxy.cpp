#include <iostream>

#include "gen-cpp2/Calculator.h" // From generated code
#include <thrift/lib/cpp2/server/ThriftServer.h>
#include <pthread.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>
#include <folly/futures/Future.h>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::async;
using namespace example::cpp2;
using namespace folly::wangle;

// This wrapper is used to capture unique_ptr<Callback> inside
// Lambda. There is no proper way to capture uniqie_ptr
// in lambdas, this wrapper is simply a workaround
struct CallbackWrapper {
  std::unique_ptr<HandlerCallback<int64_t>> ptr;
  CallbackWrapper(std::unique_ptr<HandlerCallback<int64_t>>&p)
    : ptr(std::move(p)) { }
  CallbackWrapper(const CallbackWrapper& o) {
    // The static cast is not a good idea but done to workaround
    CallbackWrapper& cw = const_cast<CallbackWrapper&>(o);
    ptr = std::move(cw.ptr);
  }
};

// The calculator service. This service is a proxy service.
// It does not do the calculation itself, instead it calls
// add function on other server and sends the same response
class CalculatorSvc : public CalculatorSvIf
{
  private:
    // This function create a client object which will be used to
    // to call add function on real calculator server
    CalculatorAsyncClient* getClient(TEventBase* ev)
    {
      int port_ = 9091;
      // Create async client socket
      std::shared_ptr<TAsyncSocket> socket(
          TAsyncSocket::newSocket(ev, "127.0.0.1", port_));
      // Create HeaderClientChannel
      auto client_channel = HeaderClientChannel::newChannel(socket);
      // Create client object
      return new CalculatorAsyncClient(std::move(client_channel));
    }
  public:
    virtual ~CalculatorSvc() {}
    void async_tm_add(
        std::unique_ptr<apache::thrift::HandlerCallback<int64_t>> callback,
        int32_t num1,
        int32_t num2)
    {
      cout << "Got async request in proxy " << num1 << " + " << num2 << endl;
      TEventBase* te = callback->getEventBase();
      // Create Callback wrapper so that it can be captured in lambda
      CallbackWrapper cb(callback);
      // The async_tm_add function is called in a different thread than the
      // thread which received the request from the network. Since we are going
      // make an async request to another server, current thread must be in an
      // event loop but the current thread is not in any event loop. So will
      // make the network call in the thread which actually received request
      // from client.
      te->runInEventBaseThread([num1, num2, cb, this]() {
          // Get the client handle of the real calculator server
          CalculatorAsyncClient* client = getClient(cb.ptr->getEventBase());;
          // Make the add function call on the real server
          //folly::wangle::Future<int64_t> f = client->future_add(num1, num2);
          folly::Future<int64_t> f = client->future_add(num1, num2);
          f.then(
            [cb](folly::Try<int64_t>&& t) {
            // Now we have received the response from real calculator server
            // respond to the client with the same result
            cout << "Received response from other server" << endl;
            cb.ptr->result(t.value());
            });
          });
    }
};

int main(int argc, char **argv) {
  // The code in the main function same as in previous example except
  // the port number. This proxy calculator will listen on 9092. So the
  // client will have to connect to 9092 now.
  // 9091   --> 9092  --> 9092
  // server --> proxy --> client
  std::shared_ptr<CalculatorSvc> ptr(new  CalculatorSvc());
  ThriftServer* s = new ThriftServer();
  s->setInterface(ptr);
  s->setPort(9092);
  s->serve();

  return 0;
}
