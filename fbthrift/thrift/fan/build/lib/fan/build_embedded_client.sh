/usr/local/gcc49/bin/g++49 -o embedded_client\
  embedded_client.cpp ../gen-cpp2/Calculator.cpp ../gen-cpp2/Calculator_client.cpp ../gen-cpp2/calculator_constants.cpp ../gen-cpp2/calculator_types.cpp \
  -std=c++11 -I../gen-cpp2 -I../ -I/home/wangfan/buildutil/include \
  -L/home/wangfan/buildutil/lib \
  /home/wangfan/fbthrift/thrift/lib/cpp2/.libs/libthriftcpp2.a \
  /home/wangfan/fbthrift/thrift/lib/cpp2/libsaslstubs.a \
  /home/wangfan/fbthrift/thrift/lib/cpp/.libs/libthrift.a \
  -lthrift \
  -lthriftcpp2 \
  -lthrift \
  -lthriftz \
  -lfolly \
  -lboost_thread -lboost_filesystem -lboost_system -lboost_regex -lboost_context \
  -lglog \
  -lsnappy \
  -lgflags \
  -ldouble-conversion \
  -lssl \
  -lcrypto \
  -levent \
  -llzma \
  -lz \
  -ldl \
  -lnuma \
  -lkrb5 \
  -lgssapi_krb5 \
  -lsasl2 \
  -lssl \
  -lrt \
  -lpthread
