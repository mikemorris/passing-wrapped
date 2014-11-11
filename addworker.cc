#include "addworker.h"

AddWorker::AddWorker(MyObject* obj1, MyObject* obj2, NanCallback *callback)
  : NanAsyncWorker(callback),
  obj1_(obj1),
  obj2_(obj2) {}

AddWorker::~AddWorker() {}

void AddWorker::Execute() {
  sum = obj1_->Val() + obj2_->Val();
}

void AddWorker::HandleOKCallback() {
  NanScope();

  v8::Local<v8::Value> argv[] = {
    NanNull(),
    NanNew(sum)
  };

  callback->Call(2, argv);
};
