/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef TimeService_H
#define TimeService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "WhatTime_types.h"

namespace roctime {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class TimeServiceIf {
 public:
  virtual ~TimeServiceIf() {}
  virtual int32_t TellMeTime() = 0;
};

class TimeServiceIfFactory {
 public:
  typedef TimeServiceIf Handler;

  virtual ~TimeServiceIfFactory() {}

  virtual TimeServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(TimeServiceIf* /* handler */) = 0;
};

class TimeServiceIfSingletonFactory : virtual public TimeServiceIfFactory {
 public:
  TimeServiceIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<TimeServiceIf>& iface) : iface_(iface) {}
  virtual ~TimeServiceIfSingletonFactory() {}

  virtual TimeServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(TimeServiceIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<TimeServiceIf> iface_;
};

class TimeServiceNull : virtual public TimeServiceIf {
 public:
  virtual ~TimeServiceNull() {}
  int32_t TellMeTime() {
    int32_t _return = 0;
    return _return;
  }
};


class TimeService_TellMeTime_args {
 public:

  TimeService_TellMeTime_args(const TimeService_TellMeTime_args&);
  TimeService_TellMeTime_args& operator=(const TimeService_TellMeTime_args&);
  TimeService_TellMeTime_args() {
  }

  virtual ~TimeService_TellMeTime_args() throw();

  bool operator == (const TimeService_TellMeTime_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TimeService_TellMeTime_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TimeService_TellMeTime_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TimeService_TellMeTime_pargs {
 public:


  virtual ~TimeService_TellMeTime_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TimeService_TellMeTime_result__isset {
  _TimeService_TellMeTime_result__isset() : success(false) {}
  bool success :1;
} _TimeService_TellMeTime_result__isset;

class TimeService_TellMeTime_result {
 public:

  TimeService_TellMeTime_result(const TimeService_TellMeTime_result&);
  TimeService_TellMeTime_result& operator=(const TimeService_TellMeTime_result&);
  TimeService_TellMeTime_result() : success(0) {
  }

  virtual ~TimeService_TellMeTime_result() throw();
  int32_t success;

  _TimeService_TellMeTime_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const TimeService_TellMeTime_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const TimeService_TellMeTime_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TimeService_TellMeTime_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TimeService_TellMeTime_presult__isset {
  _TimeService_TellMeTime_presult__isset() : success(false) {}
  bool success :1;
} _TimeService_TellMeTime_presult__isset;

class TimeService_TellMeTime_presult {
 public:


  virtual ~TimeService_TellMeTime_presult() throw();
  int32_t* success;

  _TimeService_TellMeTime_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class TimeServiceClient : virtual public TimeServiceIf {
 public:
  TimeServiceClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  TimeServiceClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t TellMeTime();
  void send_TellMeTime();
  int32_t recv_TellMeTime();
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class TimeServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<TimeServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (TimeServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_TellMeTime(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  TimeServiceProcessor(::apache::thrift::stdcxx::shared_ptr<TimeServiceIf> iface) :
    iface_(iface) {
    processMap_["TellMeTime"] = &TimeServiceProcessor::process_TellMeTime;
  }

  virtual ~TimeServiceProcessor() {}
};

class TimeServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  TimeServiceProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< TimeServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< TimeServiceIfFactory > handlerFactory_;
};

class TimeServiceMultiface : virtual public TimeServiceIf {
 public:
  TimeServiceMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<TimeServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~TimeServiceMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<TimeServiceIf> > ifaces_;
  TimeServiceMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<TimeServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  int32_t TellMeTime() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->TellMeTime();
    }
    return ifaces_[i]->TellMeTime();
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class TimeServiceConcurrentClient : virtual public TimeServiceIf {
 public:
  TimeServiceConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  TimeServiceConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t TellMeTime();
  int32_t send_TellMeTime();
  int32_t recv_TellMeTime(const int32_t seqid);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

} // namespace

#endif
