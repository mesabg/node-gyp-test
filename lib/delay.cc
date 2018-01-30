// hello.cc
#include <node.h>
#include <v8.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>

using namespace v8;
using namespace std;
using namespace std::chrono_literals;

namespace Wrapper {
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Value;

    void foo(){
        this_thread::sleep_for(2s);
        cout << "This is printed after 2s\n";
    }

    void bar(int x){
        this_thread::sleep_for(5s);
        cout << "This is printed after 5s [value is - " << x << "]\n";
    }

    void Method(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        cout << "This is printed from c++ itself" << endl;

        thread first (foo);
        thread second (bar, 28);
        cout << "hello(method), foo and bar now execute concurrently...\n";

        first.join();
        second.join();  
        cout << "foo and bar completed.\n";
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, "This is returned value; Hello world from c++"));
    }

    void init(Handle<Object> exports) {
        // add the async function to the exports for this object
        NODE_SET_METHOD(exports, "hello", Method);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, init);
}