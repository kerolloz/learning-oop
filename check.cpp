#include <iostream>
#include <cstring>
#include <sstream>
#include "checker.hpp"
#define endl '\n'
#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace demo
{
using namespace v8;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;
using v8::Value;

template <typename T>
std::string to_string(const T &n)
{
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

string verify(int questionNumber)
{
    string exercisesDir = "exercises/";
    string questionDir = "exercise-" + to_string(questionNumber) + "/";
    Checker c(exercisesDir + questionDir + "tester.cpp");
    cout << "Testing Question #" << questionNumber << ":" << endl;
    if (Compilation::SUCCESS == c.compile())
    {
        if (Test::SUCCESS == c.test())
        {
            return "CORRECT Answer!";
        }
        else
        {
            return "WRONG Answer.";
        }
    }
    else
    {
        return "Compilation ERROR";
    }
}

void Method(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();

    args.GetReturnValue().Set(String::NewFromUtf8(
                                  isolate, verify(args[0].As<Number>()->Value()).c_str(), NewStringType::kNormal)
                                  .ToLocalChecked());
}

void Initialize(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "verify", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace demo
