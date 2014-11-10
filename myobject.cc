#include <node.h>
#include "myobject.h"

MyObject::MyObject() {};
MyObject::~MyObject() {};

v8::Persistent<v8::Function> MyObject::constructor;

void MyObject::Init() {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew("MyObject"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanAssignPersistent(constructor, tpl->GetFunction());
}

NAN_METHOD(MyObject::New) {
  NanScope();

  MyObject* obj = new MyObject();
  obj->val_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> MyObject::NewInstance(v8::Local<v8::Value> arg) {
  NanEscapableScope();

  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { arg };
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return NanEscapeScope(instance);
}
