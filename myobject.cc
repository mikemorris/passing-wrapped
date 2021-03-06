#include <node.h>
#include "myobject.h"

MyObject::MyObject() {};
MyObject::~MyObject() {};

v8::Persistent<v8::Function> MyObject::constructor;

void MyObject::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew("MyObject"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "set", Set);

  NanAssignPersistent(constructor, tpl->GetFunction());

  exports->Set(NanNew("MyObject"),
      NanNew<v8::FunctionTemplate>(NewInstance)->GetFunction());
}

NAN_METHOD(MyObject::New) {
  NanScope();

  MyObject* obj = new MyObject();
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

NAN_METHOD(MyObject::NewInstance) {
  NanScope();

  if (!args.IsConstructCall())
  {
      NanThrowError("Cannot call constructor as function, you need to use 'new' keyword");
      NanReturnUndefined();
  }

  const unsigned argc = 0;
  v8::Local<v8::Value> argv[argc] = {};
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  NanReturnValue(instance);
}

NAN_METHOD(MyObject::Set) {
  NanScope();

  MyObject* obj = node::ObjectWrap::Unwrap<MyObject>(args.This());
  obj->val_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();

  NanReturnValue(args.This());
}
