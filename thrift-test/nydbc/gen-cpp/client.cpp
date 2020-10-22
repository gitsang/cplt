#include <iostream>
 
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
 
#include "nydbc.h"
 
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace com::yealink::dbc::idl;
 
typedef apache::thrift::stdcxx::shared_ptr<TSocket> TSocket_sp;
typedef apache::thrift::stdcxx::shared_ptr<TProtocol> TProtocol_sp;
typedef apache::thrift::stdcxx::shared_ptr<TTransport> TTransport_sp;
typedef apache::thrift::stdcxx::shared_ptr<TFramedTransport> TFramedTransport_sp;
typedef apache::thrift::stdcxx::shared_ptr<nydbcClient> nydbc_client_sp;
 
int main() {
    std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090)
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket)
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport)
    nydbcClient client(protocol)
 
    try {
        transport->open(
 
        //client.ping(
        //cout << "ping()" << endl;
        //transport->close(
    } catch (Exception& e) {
        cout << "ERROR: " << e.what() << endl;
    }
}
 
#define GET_NC \
        if (!cs.get() || !cs->is_ok()) { \
            LOG(ERROR) << __FUNCTION__ << " conn_socket is no ok"; \
            return false; \
        } \
        nydbc_client_sp ncli = cs->get_nydbc(); \
        if (!ncli.get()) { \
            LOG(ERROR) << __FUNCTION__ << " get nydbc client is failed"; \
            return false; \
        }
