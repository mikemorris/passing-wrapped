#include <nan.h>
#include "myobject.h"

NAN_METHOD(CreateObject) {
  NanScope();
  NanReturnValue(MyObject::NewInstance(args[0]));
}

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
  MyObject::Init();

  exports->Set(NanNew("createObject"),
      NanNew<v8::FunctionTemplate>(CreateObject)->GetFunction());

  exports->Set(NanNew("add"),
      NanNew<v8::FunctionTemplate>(Add)->GetFunction());
}

NODE_MODULE(addon, InitAll)
