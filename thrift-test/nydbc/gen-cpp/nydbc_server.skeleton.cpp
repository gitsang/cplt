// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "nydbc.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::com::yealink::dbc::idl;

class nydbcHandler : virtual public nydbcIf {
 public:
  nydbcHandler() {
    // Your initialization goes here
  }

  bool ping() {
    // Your implementation goes here
    printf("ping\n");
  }

  void start(sql_batch& _return, const sql_batch_filter& filter) {
    // Your implementation goes here
    printf("start\n");
  }

  bool commit(const sql_batch& batch) {
    // Your implementation goes here
    printf("commit\n");
  }

  bool rollback(const sql_batch& batch) {
    // Your implementation goes here
    printf("rollback\n");
  }

  void lock(std::string& _return, const db_lock& lock) {
    // Your implementation goes here
    printf("lock\n");
  }

  bool unlock(const std::string& lock, const std::string& owner) {
    // Your implementation goes here
    printf("unlock\n");
  }

  bool uplock(const std::string& lock, const std::string& owner, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("uplock\n");
  }

  void sql_query(std::vector<std::map<std::string, std::string> > & _return, const sql_query_filter& filter) {
    // Your implementation goes here
    printf("sql_query\n");
  }

  int64_t sql_update(const sql_update_filter& filter) {
    // Your implementation goes here
    printf("sql_update\n");
  }

  void sql_update_with_return(sql_update_return& _return, const sql_update_filter& filter) {
    // Your implementation goes here
    printf("sql_update_with_return\n");
  }

  bool redis_pexpire(const std::string& key, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_pexpire\n");
  }

  int64_t redis_del(const redis_del_filter& filter) {
    // Your implementation goes here
    printf("redis_del\n");
  }

  int64_t redis_incrby(const std::string& key, const int64_t step) {
    // Your implementation goes here
    printf("redis_incrby\n");
  }

  bool redis_set(const redis_set_filter& filter) {
    // Your implementation goes here
    printf("redis_set\n");
  }

  void redis_get(std::string& _return, const std::string& key) {
    // Your implementation goes here
    printf("redis_get\n");
  }

  bool redis_hset(const std::string& key, const std::string& hkey, const std::string& value) {
    // Your implementation goes here
    printf("redis_hset\n");
  }

  bool redis_hmset(const std::string& key, const std::map<std::string, std::string> & fvs) {
    // Your implementation goes here
    printf("redis_hmset\n");
  }

  int64_t redis_hdel(const std::string& key, const std::string& hkey) {
    // Your implementation goes here
    printf("redis_hdel\n");
  }

  int64_t redis_hmdel(const std::string& key, const std::set<std::string> & hkeys) {
    // Your implementation goes here
    printf("redis_hmdel\n");
  }

  void redis_hget(std::string& _return, const std::string& key, const std::string& hkey) {
    // Your implementation goes here
    printf("redis_hget\n");
  }

  void redis_hmget(std::map<std::string, std::string> & _return, const std::string& key, const std::set<std::string> & hks) {
    // Your implementation goes here
    printf("redis_hmget\n");
  }

  int64_t redis_hlen(const std::string& key) {
    // Your implementation goes here
    printf("redis_hlen\n");
  }

  void redis_hgetall(std::map<std::string, std::string> & _return, const std::string& key) {
    // Your implementation goes here
    printf("redis_hgetall\n");
  }

  void redis_keys(std::vector<std::string> & _return, const std::string& reg) {
    // Your implementation goes here
    printf("redis_keys\n");
  }

  bool redis_hsetex(const std::string& key, const std::string& hkey, const std::string& value, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_hsetex\n");
  }

  bool redis_hmsetex(const std::string& key, const std::vector<redis_hmsetex_filter> & fvts) {
    // Your implementation goes here
    printf("redis_hmsetex\n");
  }

  void redis_hgetex(std::string& _return, const std::string& key, const std::string& hkey) {
    // Your implementation goes here
    printf("redis_hgetex\n");
  }

  void redis_hmgetex(std::map<std::string, std::string> & _return, const std::string& key, const std::set<std::string> & hkeys) {
    // Your implementation goes here
    printf("redis_hmgetex\n");
  }

  bool redis_hexpire(const std::string& key, const std::string& field, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_hexpire\n");
  }

  int64_t redis_hdelex(const std::string& key, const std::set<std::string> & hkeys) {
    // Your implementation goes here
    printf("redis_hdelex\n");
  }

  int64_t redis_hlenex(const std::string& key) {
    // Your implementation goes here
    printf("redis_hlenex\n");
  }

  void redis_hgetallex(std::map<std::string, std::string> & _return, const std::string& key) {
    // Your implementation goes here
    printf("redis_hgetallex\n");
  }

  bool redis_pexpireex(const std::string& key, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_pexpireex\n");
  }

  /**
   * **************************region*************************
   * 
   * @param filter
   */
  void get_region(std::vector<region_out> & _return, const region_filter& filter) {
    // Your implementation goes here
    printf("get_region\n");
  }

  bool put_region(const std::vector<region> & regions) {
    // Your implementation goes here
    printf("put_region\n");
  }

  /**
   * ********************redis_global_************************
   * 
   * @param key
   * @param hold_time_mseconds
   */
  bool redis_global_pexpire(const std::string& key, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_global_pexpire\n");
  }

  int64_t redis_global_del(const redis_del_filter& filter) {
    // Your implementation goes here
    printf("redis_global_del\n");
  }

  bool redis_global_set(const redis_set_filter& filter) {
    // Your implementation goes here
    printf("redis_global_set\n");
  }

  bool redis_global_hset(const std::string& key, const std::string& hkey, const std::string& value) {
    // Your implementation goes here
    printf("redis_global_hset\n");
  }

  bool redis_global_hmset(const std::string& key, const std::map<std::string, std::string> & fvs) {
    // Your implementation goes here
    printf("redis_global_hmset\n");
  }

  int64_t redis_global_hdel(const std::string& key, const std::string& hkey) {
    // Your implementation goes here
    printf("redis_global_hdel\n");
  }

  int64_t redis_global_hmdel(const std::string& key, const std::set<std::string> & hkeys) {
    // Your implementation goes here
    printf("redis_global_hmdel\n");
  }

  bool redis_global_hsetex(const std::string& key, const std::string& hkey, const std::string& value, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_global_hsetex\n");
  }

  bool redis_global_hmsetex(const std::string& key, const std::vector<redis_hmsetex_filter> & fvts) {
    // Your implementation goes here
    printf("redis_global_hmsetex\n");
  }

  bool redis_global_hexpire(const std::string& key, const std::string& field, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_global_hexpire\n");
  }

  int64_t redis_global_hdelex(const std::string& key, const std::set<std::string> & hkeys) {
    // Your implementation goes here
    printf("redis_global_hdelex\n");
  }

  bool redis_global_pexpireex(const std::string& key, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_global_pexpireex\n");
  }

  /**
   * ********************redis_peer_************************
   * 
   * @param key
   * @param hold_time_mseconds
   */
  bool redis_peer_pexpire(const std::string& key, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_peer_pexpire\n");
  }

  int64_t redis_peer_del(const redis_del_filter& filter) {
    // Your implementation goes here
    printf("redis_peer_del\n");
  }

  bool redis_peer_set(const redis_set_filter& filter) {
    // Your implementation goes here
    printf("redis_peer_set\n");
  }

  bool redis_peer_hset(const std::string& key, const std::string& hkey, const std::string& value) {
    // Your implementation goes here
    printf("redis_peer_hset\n");
  }

  bool redis_peer_hmset(const std::string& key, const std::map<std::string, std::string> & fvs) {
    // Your implementation goes here
    printf("redis_peer_hmset\n");
  }

  int64_t redis_peer_hdel(const std::string& key, const std::string& hkey) {
    // Your implementation goes here
    printf("redis_peer_hdel\n");
  }

  int64_t redis_peer_hmdel(const std::string& key, const std::set<std::string> & hkeys) {
    // Your implementation goes here
    printf("redis_peer_hmdel\n");
  }

  bool redis_peer_hsetex(const std::string& key, const std::string& hkey, const std::string& value, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_peer_hsetex\n");
  }

  bool redis_peer_hmsetex(const std::string& key, const std::vector<redis_hmsetex_filter> & fvts) {
    // Your implementation goes here
    printf("redis_peer_hmsetex\n");
  }

  bool redis_peer_hexpire(const std::string& key, const std::string& field, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_peer_hexpire\n");
  }

  int64_t redis_peer_hdelex(const std::string& key, const std::set<std::string> & hkeys) {
    // Your implementation goes here
    printf("redis_peer_hdelex\n");
  }

  bool redis_peer_pexpireex(const std::string& key, const int64_t hold_time_mseconds) {
    // Your implementation goes here
    printf("redis_peer_pexpireex\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::apache::thrift::stdcxx::shared_ptr<nydbcHandler> handler(new nydbcHandler());
  ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new nydbcProcessor(handler));
  ::apache::thrift::stdcxx::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
