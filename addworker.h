#ifndef ADDWORKER_H
#define ADDWORKER_H

#include <nan.h>
#include "myobject.h"

class AddWorker : public NanAsyncWorker {
public:
  AddWorker(MyObject* obj1, MyObject* obj2, NanCallback *callback);
  ~AddWorker();

  void Execute();
  void HandleOKCallback();

private:
  MyObject* obj1_;
  MyObject* obj2_;
  double sum;
};

#endif
