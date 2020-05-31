#ifdef DEBUG
#define MyLog NSLog
#else
#define MyLog(...) (void)printf("%s\n",[[NSString stringWithFormat:__VA_ARGS__] UTF8String])
#endif

#include <Foundation/Foundation.h>
#include <AppKit/NSScreen.h>
#include "ddcctl/DDC.h"
#include "functions.h"

NAN_METHOD(nothing)
{
}

NAN_METHOD(aString)
{
  info.GetReturnValue().Set(Nan::New("This is a thing.").ToLocalChecked());
}

NAN_METHOD(aBoolean)
{
  info.GetReturnValue().Set(false);
}

NAN_METHOD(aNumber)
{
  info.GetReturnValue().Set(1.75);
}

NAN_METHOD(anObject)
{
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  Nan::Set(obj, Nan::New("key").ToLocalChecked(), Nan::New("value").ToLocalChecked());
  info.GetReturnValue().Set(obj);
}

NAN_METHOD(anArray)
{
  v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
  Nan::Set(arr, 0, Nan::New(1));
  Nan::Set(arr, 1, Nan::New(2));
  Nan::Set(arr, 2, Nan::New(3));
  info.GetReturnValue().Set(arr);
}

NAN_METHOD(callback)
{
  v8::Local<v8::Function> callbackHandle = info[0].As<v8::Function>();
  Nan::AsyncResource *resource = new Nan::AsyncResource(Nan::New<v8::String>("MyObject:CallCallback").ToLocalChecked());
  resource->runInAsyncScope(Nan::GetCurrentContext()->Global(), callbackHandle, 0, 0);
}

NAN_METHOD(callbackWithParameter)
{
  v8::Local<v8::Function> callbackHandle = info[0].As<v8::Function>();
  Nan::AsyncResource *resource = new Nan::AsyncResource(Nan::New<v8::String>("MyObject:CallCallbackWithParam").ToLocalChecked());
  int argc = 1;
  v8::Local<v8::Value> argv[] = {
      Nan::New("parameter test").ToLocalChecked()};
  resource->runInAsyncScope(Nan::GetCurrentContext()->Global(), callbackHandle, argc, argv);
}

v8::Local<v8::Object> getScreenInfo(NSScreen *screen)
{

  NSDictionary *description = [screen deviceDescription];
  CGDirectDisplayID id = [[description objectForKey:@"NSScreenNumber"] unsignedIntValue];
  NSSize displayPixelSize = [[description objectForKey:NSDeviceSize] sizeValue];
  CGSize displayPhysicalSize = CGDisplayScreenSize(id);
  float displayScale = [screen backingScaleFactor];
  double rotation = CGDisplayRotation(id);

  v8::Local<v8::Object> deviceInfo = Nan::New<v8::Object>();
  v8::Local<v8::Object> deviceSize = Nan::New<v8::Object>();
  v8::Local<v8::Object> deviceSizePixel = Nan::New<v8::Object>();
  v8::Local<v8::Object> deviceSizePhysical = Nan::New<v8::Object>();

  Nan::Set(
      deviceInfo,
      Nan::New("id")
          .ToLocalChecked(),
      Nan::New(id));

  NSString *uuid = (NSString *)CFUUIDCreateString(NULL, CGDisplayCreateUUIDFromDisplayID(id));

  Nan::Set(
      deviceInfo,
      Nan::New("uuid")
          .ToLocalChecked(),
      Nan::New([uuid cStringUsingEncoding:NSASCIIStringEncoding])
          .ToLocalChecked()
  );

  Nan::Set(
      deviceInfo,
      Nan::New("model")
          .ToLocalChecked(),
      Nan::New(CGDisplayIsBuiltin(id)));

  Nan::Set(
      deviceInfo,
      Nan::New("serialNumber")
          .ToLocalChecked(),
      Nan::New(CGDisplaySerialNumber(id)));

  Nan::Set(
      deviceInfo,
      Nan::New("isBuiltIn")
          .ToLocalChecked(),
      Nan::New<v8::Boolean>(CGDisplayIsBuiltin(id)));

  Nan::Set(
      deviceInfo,
      Nan::New("displayScale")
          .ToLocalChecked(),
      Nan::New(displayScale));

  Nan::Set(
      deviceSizePixel,
      Nan::New("width")
          .ToLocalChecked(),
      Nan::New(displayPixelSize.width));
  Nan::Set(
      deviceSizePixel,
      Nan::New("height")
          .ToLocalChecked(),
      Nan::New(displayPixelSize.height));
  Nan::Set(
      deviceSizePhysical,
      Nan::New("width")
          .ToLocalChecked(),
      Nan::New(displayPhysicalSize.width));
  Nan::Set(
      deviceSizePhysical,
      Nan::New("height")
          .ToLocalChecked(),
      Nan::New(displayPhysicalSize.height));

  Nan::Set(
      deviceSize,
      Nan::New("pixel")
          .ToLocalChecked(),
      deviceSizePixel);
  Nan::Set(
      deviceSize,
      Nan::New("physical")
          .ToLocalChecked(),
      deviceSizePhysical);

  Nan::Set(
      deviceInfo,
      Nan::New("size")
          .ToLocalChecked(),
      deviceSize);

  Nan::Set(
      deviceInfo,
      Nan::New("rotation")
          .ToLocalChecked(),
      Nan::New(rotation));

  return deviceInfo;
}

NAN_METHOD(mainn)
{
  v8::Local<v8::Array> screens = Nan::New<v8::Array>(NSScreen.screens.count);
  unsigned long i = 0;
  for (NSScreen *screen in NSScreen.screens)
  {
    NSDictionary *description = [screen deviceDescription];
    if ([description objectForKey:@"NSDeviceIsScreen"])
    {
      Nan::Set(screens, i++, getScreenInfo(screen));
    }
  }
  info.GetReturnValue().Set(screens);
}

CGDirectDisplayID getDisplayByUUID(v8::Local<v8::Value> info) {
  Nan::Utf8String *s = new Nan::Utf8String(info);


  CFUUIDRef uuidRef = CFUUIDCreateFromString(
    NULL,
    (CFStringRef)**s
  );

  return CGDisplayGetDisplayIDFromUUID(uuidRef);
}

NAN_METHOD(setControl)
{
  CGDirectDisplayID cdisplay = getDisplayByUUID(info[0]);

  struct DDCWriteCommand command;
  command.control_id = Nan::To<uint>(info[1]).FromJust();
  command.new_value = Nan::To<uint>(info[2]).FromJust();

  if (!DDCWrite(cdisplay, &command)) {
    MyLog(@"E: Failed to send DDC command!");
  }
}

NAN_METHOD(getControl)
{
  CGDirectDisplayID cdisplay = getDisplayByUUID(info[0]);
  
  struct DDCReadCommand command;
  
  command.control_id = Nan::To<uint>(info[1]).FromJust();
  command.max_value = 0;
  command.current_value = 0;

  MyLog(@"D: querying VCP control: #%u =?", command.control_id);

  v8::Local<v8::Object> result = Nan::New<v8::Object>();
  v8::Local<v8::Value> error;

  if (!DDCRead(cdisplay, &command)) {
      MyLog(@"E: DDC send command failed!");
      MyLog(@"E: VCP control #%u (0x%02hhx) = current: %u, max: %u", command.control_id, command.control_id, command.current_value, command.max_value);
      v8::Local<v8::Value> error = Nan::Error("err");
  } else {
      MyLog(@"I: VCP control #%u (0x%02hhx) = current: %u, max: %u", command.control_id, command.control_id, command.current_value, command.max_value);
      Nan::Set(result,
        Nan::New("value").ToLocalChecked(),
        Nan::New(command.current_value)
      );
  }

  v8::Local<v8::Function> callbackHandle = info[4].As<v8::Function>();
  Nan::AsyncResource *resource = new Nan::AsyncResource(Nan::New<v8::String>("MyObject:CallCallbackWithParam").ToLocalChecked());
  int argc = 2;
  v8::Local<v8::Value> argv[] = { error, result };
  resource->runInAsyncScope(Nan::GetCurrentContext()->Global(), callbackHandle, argc, argv);
}

// Wrapper Impl

Nan::Persistent<v8::Function> MyObject::constructor;

NAN_MODULE_INIT(MyObject::Init)
{
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "plusOne", PlusOne);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("MyObject").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

MyObject::MyObject(double value) : value_(value)
{
}

MyObject::~MyObject()
{
}

NAN_METHOD(MyObject::New)
{
  if (info.IsConstructCall())
  {
    double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
    MyObject *obj = new MyObject(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  }
  else
  {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
  }
}

NAN_METHOD(MyObject::PlusOne)
{
  MyObject *obj = Nan::ObjectWrap::Unwrap<MyObject>(info.This());
  obj->value_ += 1;
  info.GetReturnValue().Set(obj->value_);
}
