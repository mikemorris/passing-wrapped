#include <nan.h>
#include "myobject.h"
#include "addworker.h"

NAN_METHOD(Add) {
  NanScope();

  MyObject* obj1 = node::ObjectWrap::Unwrap<MyObject>(
      args[0]->ToObject());
  MyObject* obj2 = node::ObjectWrap::Unwrap<MyObject>(
      args[1]->ToObject());

  NanCallback *callback = new NanCallback(args[2].As<v8::Function>());

  NanAsyncQueueWorker(new AddWorker(obj1, obj2, callback));

  NanReturnUndefined();
}

void InitAll(v8::Handle<v8::Object> exports) {
  MyObject::Init(exports);

  exports->Set(NanNew("add"),
      NanNew<v8::FunctionTemplate>(Add)->GetFunction());
}

NODE_MODULE(addon, InitAll)
