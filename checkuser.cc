#ifndef UNICODE
#define UNICODE
#endif

#pragma comment(lib, "netapi32.lib")

#include <windows.h>
#include <lmaccess.h>
#include <atlstr.h>
#include "./napi.h"

Napi::Value Check(const Napi::CallbackInfo& info)
{
    USER_INFO_0* buffer;
    DWORD entries;
    DWORD total_entries;
    DWORD resume_handle = 0;

    NET_API_STATUS a = NetUserEnum(
        NULL,
        0, 0,
        (BYTE**)&buffer,
        4096,
        &entries,
        &total_entries,
        &resume_handle
    );

    Napi::Env env = info.Env();

    if (info.Length() != 1) {
        Napi::TypeError::New(env, "Wrong number of arguments")
            .ThrowAsJavaScriptException();

        return env.Null();
    }

    bool flag = false;

    std::string userName = info[0].As<Napi::String>();

    for (unsigned i = 0; i < entries; i++)
    {
        std::string user = std::string(CW2A(buffer[i].usri0_name, CP_UTF8));

        if (user == userName)
        {
            flag = true;

            break;
        }
    }

    Napi::Boolean res = Napi::Boolean::New(env, flag);

    return res;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "check"), Napi::Function::New(env, Check));

    return exports;
}

NODE_API_MODULE(checkuser, Init);