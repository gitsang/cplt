#include "TimeService.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
 
#include <iostream>

using namespace std;
 
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
 
using namespace roctime;
 
int main(int argc, char *argv[]) {
    std::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
     
    time_t mytime = 0;
     
    TimeServiceClient client(protocol);
    transport->open();
    mytime = client.TellMeTime();
     
    cout << "Now is " << ctime(&mytime) << endl;
    transport->close();
     
    return 0;
}
