#include <iostream>

#include "gen-cpp2/Calculator.h" // This is included from generated code
#include <thrift/lib/cpp2/server/ThriftServer.h>

using namespace std;
using namespace apache::thrift;
using namespace example::cpp2;

//The thrift has generated service interface with name CalculatorSvIf
// At server side we have to implement this interface
class CalculatorSvc : public CalculatorSvIf
{
  public:
    virtual ~CalculatorSvc() {}
    // We have to implement async_tm_add to implement the add function
    // of the Calculator service which we defined in calculator.thrift file
    void async_tm_add(
        // callback is passed to this function to return result of the add
        // operation. Since we are implementing the service in async way
        // the return type of function is void and result is returned via
        // callback. The function may immediately return and later when
        // the result is ready then it will return the result via
        // callback. In this example, we are returning the result
        // before returning the function but this may not be always true.
        std::unique_ptr<apache::thrift::HandlerCallback<int64_t>> callback,
        // num1 is a parameter of add function. Its value will be passed from client
        int32_t num1,
        // num2 is another parameter of add function. Its value will be passed from client
        int32_t num2)
    {
      cout << "Got async request " << num1 << " + " << num2 << endl;
      callback->result(num1 + num2); // return the result via callback
    }
};

int main(int argc, char **argv) {
  // To create a server, we need to first create server handler object.
  // The server handler object contains the implementation of the service.
  std::shared_ptr<CalculatorSvc> ptr(new  CalculatorSvc());
  // Create a thrift server
  ThriftServer* s = new ThriftServer();
  // Set server handler object
  s->setInterface(ptr);
  // Set the server port
  s->setPort(9091);
  // Start the server to serve!!
  s->serve();

  return 0;
}
