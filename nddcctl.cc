#include <Foundation/Foundation.h>
#include <AppKit/NSScreen.h>

#include "ddcctl/DDC.h"
#include "functions.h"

using v8::FunctionTemplate;

// NativeExtension.cc represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("nothing").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(nothing)).ToLocalChecked());
  Nan::Set(target, Nan::New("aString").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(aString)).ToLocalChecked());
  Nan::Set(target, Nan::New("aBoolean").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(aBoolean)).ToLocalChecked());
  Nan::Set(target, Nan::New("aNumber").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(aNumber)).ToLocalChecked());
  Nan::Set(target, Nan::New("anObject").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(anObject)).ToLocalChecked());
  Nan::Set(target, Nan::New("anArray").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(anArray)).ToLocalChecked());
  Nan::Set(target, Nan::New("callback").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(callback)).ToLocalChecked());
  Nan::Set(target, Nan::New("callbackWithParameter").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(callbackWithParameter)).ToLocalChecked());
  // Nan::Set(target, Nan::New("write").ToLocalChecked(),
  //   Nan::GetFunction(Nan::New<FunctionTemplate>(DDCWrite)).ToLocalChecked());
  // Nan::Set(target, Nan::New("read").ToLocalChecked(),
  //   Nan::GetFunction(Nan::New<FunctionTemplate>(DDCRead)).ToLocalChecked());
  // Nan::Set(target, Nan::New("test").ToLocalChecked(),
  //   Nan::GetFunction(Nan::New<FunctionTemplate>(EDIDTest)).ToLocalChecked());
  Nan::Set(target, Nan::New("mainn").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(mainn)).ToLocalChecked());
  Nan::Set(target, Nan::New("getControl").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(getControl)).ToLocalChecked());
  Nan::Set(target, Nan::New("setControl").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(setControl)).ToLocalChecked());

  // Passing target down to the next NAN_MODULE_INIT
  MyObject::Init(target);
}

NODE_MODULE(nddcctl, InitAll)
