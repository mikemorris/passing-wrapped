#include <nan.h>
#include "myobject.h"

NAN_METHOD(Add) {
  NanScope();

  MyObject* obj1 = node::ObjectWrap::Unwrap<MyObject>(
      args[0]->ToObject());
  MyObject* obj2 = node::ObjectWrap::Unwrap<MyObject>(
      args[1]->ToObject());

  double sum = obj1->Val() + obj2->Val();
  NanReturnValue(NanNew(sum));
}

void InitAll(v8::Handle<v8::Object> exports) {
  MyObject::Init(exports);

  exports->Set(NanNew("add"),
      NanNew<v8::FunctionTemplate>(Add)->GetFunction());
}

NODE_MODULE(addon, InitAll)
