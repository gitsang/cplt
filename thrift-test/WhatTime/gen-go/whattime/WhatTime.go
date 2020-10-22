// Autogenerated by Thrift Compiler (0.11.0)
// DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING

package whattime

import (
	"bytes"
	"reflect"
	"context"
	"fmt"
	"git.apache.org/thrift.git/lib/go/thrift"
)

// (needed to ensure safety because of naive import list construction.)
var _ = thrift.ZERO
var _ = fmt.Printf
var _ = context.Background
var _ = reflect.DeepEqual
var _ = bytes.Equal

type TimeService interface {
  TellMeTime(ctx context.Context) (r int32, err error)
}

type TimeServiceClient struct {
  c thrift.TClient
}

// Deprecated: Use NewTimeService instead
func NewTimeServiceClientFactory(t thrift.TTransport, f thrift.TProtocolFactory) *TimeServiceClient {
  return &TimeServiceClient{
    c: thrift.NewTStandardClient(f.GetProtocol(t), f.GetProtocol(t)),
  }
}

// Deprecated: Use NewTimeService instead
func NewTimeServiceClientProtocol(t thrift.TTransport, iprot thrift.TProtocol, oprot thrift.TProtocol) *TimeServiceClient {
  return &TimeServiceClient{
    c: thrift.NewTStandardClient(iprot, oprot),
  }
}

func NewTimeServiceClient(c thrift.TClient) *TimeServiceClient {
  return &TimeServiceClient{
    c: c,
  }
}

func (p *TimeServiceClient) TellMeTime(ctx context.Context) (r int32, err error) {
  var _args0 TimeServiceTellMeTimeArgs
  var _result1 TimeServiceTellMeTimeResult
  if err = p.c.Call(ctx, "TellMeTime", &_args0, &_result1); err != nil {
    return
  }
  return _result1.GetSuccess(), nil
}

type TimeServiceProcessor struct {
  processorMap map[string]thrift.TProcessorFunction
  handler TimeService
}

func (p *TimeServiceProcessor) AddToProcessorMap(key string, processor thrift.TProcessorFunction) {
  p.processorMap[key] = processor
}

func (p *TimeServiceProcessor) GetProcessorFunction(key string) (processor thrift.TProcessorFunction, ok bool) {
  processor, ok = p.processorMap[key]
  return processor, ok
}

func (p *TimeServiceProcessor) ProcessorMap() map[string]thrift.TProcessorFunction {
  return p.processorMap
}

func NewTimeServiceProcessor(handler TimeService) *TimeServiceProcessor {

  self2 := &TimeServiceProcessor{handler:handler, processorMap:make(map[string]thrift.TProcessorFunction)}
  self2.processorMap["TellMeTime"] = &timeServiceProcessorTellMeTime{handler:handler}
return self2
}

func (p *TimeServiceProcessor) Process(ctx context.Context, iprot, oprot thrift.TProtocol) (success bool, err thrift.TException) {
  name, _, seqId, err := iprot.ReadMessageBegin()
  if err != nil { return false, err }
  if processor, ok := p.GetProcessorFunction(name); ok {
    return processor.Process(ctx, seqId, iprot, oprot)
  }
  iprot.Skip(thrift.STRUCT)
  iprot.ReadMessageEnd()
  x3 := thrift.NewTApplicationException(thrift.UNKNOWN_METHOD, "Unknown function " + name)
  oprot.WriteMessageBegin(name, thrift.EXCEPTION, seqId)
  x3.Write(oprot)
  oprot.WriteMessageEnd()
  oprot.Flush()
  return false, x3

}

type timeServiceProcessorTellMeTime struct {
  handler TimeService
}

func (p *timeServiceProcessorTellMeTime) Process(ctx context.Context, seqId int32, iprot, oprot thrift.TProtocol) (success bool, err thrift.TException) {
  args := TimeServiceTellMeTimeArgs{}
  if err = args.Read(iprot); err != nil {
    iprot.ReadMessageEnd()
    x := thrift.NewTApplicationException(thrift.PROTOCOL_ERROR, err.Error())
    oprot.WriteMessageBegin("TellMeTime", thrift.EXCEPTION, seqId)
    x.Write(oprot)
    oprot.WriteMessageEnd()
    oprot.Flush()
    return false, err
  }

  iprot.ReadMessageEnd()
  result := TimeServiceTellMeTimeResult{}
var retval int32
  var err2 error
  if retval, err2 = p.handler.TellMeTime(ctx); err2 != nil {
    x := thrift.NewTApplicationException(thrift.INTERNAL_ERROR, "Internal error processing TellMeTime: " + err2.Error())
    oprot.WriteMessageBegin("TellMeTime", thrift.EXCEPTION, seqId)
    x.Write(oprot)
    oprot.WriteMessageEnd()
    oprot.Flush()
    return true, err2
  } else {
    result.Success = &retval
}
  if err2 = oprot.WriteMessageBegin("TellMeTime", thrift.REPLY, seqId); err2 != nil {
    err = err2
  }
  if err2 = result.Write(oprot); err == nil && err2 != nil {
    err = err2
  }
  if err2 = oprot.WriteMessageEnd(); err == nil && err2 != nil {
    err = err2
  }
  if err2 = oprot.Flush(); err == nil && err2 != nil {
    err = err2
  }
  if err != nil {
    return
  }
  return true, err
}


// HELPER FUNCTIONS AND STRUCTURES

type TimeServiceTellMeTimeArgs struct {
}

func NewTimeServiceTellMeTimeArgs() *TimeServiceTellMeTimeArgs {
  return &TimeServiceTellMeTimeArgs{}
}

func (p *TimeServiceTellMeTimeArgs) Read(iprot thrift.TProtocol) error {
  if _, err := iprot.ReadStructBegin(); err != nil {
    return thrift.PrependError(fmt.Sprintf("%T read error: ", p), err)
  }


  for {
    _, fieldTypeId, fieldId, err := iprot.ReadFieldBegin()
    if err != nil {
      return thrift.PrependError(fmt.Sprintf("%T field %d read error: ", p, fieldId), err)
    }
    if fieldTypeId == thrift.STOP { break; }
    if err := iprot.Skip(fieldTypeId); err != nil {
      return err
    }
    if err := iprot.ReadFieldEnd(); err != nil {
      return err
    }
  }
  if err := iprot.ReadStructEnd(); err != nil {
    return thrift.PrependError(fmt.Sprintf("%T read struct end error: ", p), err)
  }
  return nil
}

func (p *TimeServiceTellMeTimeArgs) Write(oprot thrift.TProtocol) error {
  if err := oprot.WriteStructBegin("TellMeTime_args"); err != nil {
    return thrift.PrependError(fmt.Sprintf("%T write struct begin error: ", p), err) }
  if p != nil {
  }
  if err := oprot.WriteFieldStop(); err != nil {
    return thrift.PrependError("write field stop error: ", err) }
  if err := oprot.WriteStructEnd(); err != nil {
    return thrift.PrependError("write struct stop error: ", err) }
  return nil
}

func (p *TimeServiceTellMeTimeArgs) String() string {
  if p == nil {
    return "<nil>"
  }
  return fmt.Sprintf("TimeServiceTellMeTimeArgs(%+v)", *p)
}

// Attributes:
//  - Success
type TimeServiceTellMeTimeResult struct {
  Success *int32 `thrift:"success,0" db:"success" json:"success,omitempty"`
}

func NewTimeServiceTellMeTimeResult() *TimeServiceTellMeTimeResult {
  return &TimeServiceTellMeTimeResult{}
}

var TimeServiceTellMeTimeResult_Success_DEFAULT int32
func (p *TimeServiceTellMeTimeResult) GetSuccess() int32 {
  if !p.IsSetSuccess() {
    return TimeServiceTellMeTimeResult_Success_DEFAULT
  }
return *p.Success
}
func (p *TimeServiceTellMeTimeResult) IsSetSuccess() bool {
  return p.Success != nil
}

func (p *TimeServiceTellMeTimeResult) Read(iprot thrift.TProtocol) error {
  if _, err := iprot.ReadStructBegin(); err != nil {
    return thrift.PrependError(fmt.Sprintf("%T read error: ", p), err)
  }


  for {
    _, fieldTypeId, fieldId, err := iprot.ReadFieldBegin()
    if err != nil {
      return thrift.PrependError(fmt.Sprintf("%T field %d read error: ", p, fieldId), err)
    }
    if fieldTypeId == thrift.STOP { break; }
    switch fieldId {
    case 0:
      if fieldTypeId == thrift.I32 {
        if err := p.ReadField0(iprot); err != nil {
          return err
        }
      } else {
        if err := iprot.Skip(fieldTypeId); err != nil {
          return err
        }
      }
    default:
      if err := iprot.Skip(fieldTypeId); err != nil {
        return err
      }
    }
    if err := iprot.ReadFieldEnd(); err != nil {
      return err
    }
  }
  if err := iprot.ReadStructEnd(); err != nil {
    return thrift.PrependError(fmt.Sprintf("%T read struct end error: ", p), err)
  }
  return nil
}

func (p *TimeServiceTellMeTimeResult)  ReadField0(iprot thrift.TProtocol) error {
  if v, err := iprot.ReadI32(); err != nil {
  return thrift.PrependError("error reading field 0: ", err)
} else {
  p.Success = &v
}
  return nil
}

func (p *TimeServiceTellMeTimeResult) Write(oprot thrift.TProtocol) error {
  if err := oprot.WriteStructBegin("TellMeTime_result"); err != nil {
    return thrift.PrependError(fmt.Sprintf("%T write struct begin error: ", p), err) }
  if p != nil {
    if err := p.writeField0(oprot); err != nil { return err }
  }
  if err := oprot.WriteFieldStop(); err != nil {
    return thrift.PrependError("write field stop error: ", err) }
  if err := oprot.WriteStructEnd(); err != nil {
    return thrift.PrependError("write struct stop error: ", err) }
  return nil
}

func (p *TimeServiceTellMeTimeResult) writeField0(oprot thrift.TProtocol) (err error) {
  if p.IsSetSuccess() {
    if err := oprot.WriteFieldBegin("success", thrift.I32, 0); err != nil {
      return thrift.PrependError(fmt.Sprintf("%T write field begin error 0:success: ", p), err) }
    if err := oprot.WriteI32(int32(*p.Success)); err != nil {
    return thrift.PrependError(fmt.Sprintf("%T.success (0) field write error: ", p), err) }
    if err := oprot.WriteFieldEnd(); err != nil {
      return thrift.PrependError(fmt.Sprintf("%T write field end error 0:success: ", p), err) }
  }
  return err
}

func (p *TimeServiceTellMeTimeResult) String() string {
  if p == nil {
    return "<nil>"
  }
  return fmt.Sprintf("TimeServiceTellMeTimeResult(%+v)", *p)
}


