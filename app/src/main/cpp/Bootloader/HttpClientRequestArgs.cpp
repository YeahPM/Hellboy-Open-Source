//
// Created by 93261 on 2022/10/6.
//

#include <cstring>
#include "HttpClientRequestArgs.h"

namespace HttpClientRequestArgsAddr{
    uint64_t AddHeader = 0xCBCEB4;				//HttpClientRequestArgs::AddHeader(HttpClientRequestArgs *this, const char *s, const char *a3)
    uint64_t HttpClientRequestArgs = 0xCBCE54;  //HttpClientRequestArgs::HttpClientRequestArgs(HttpRequest::HttpRequestType,void const*,uint)
}

void initHttpClientRequestArgsAddr(uint64_t bootloaderBase){
    HttpClientRequestArgsAddr::AddHeader += bootloaderBase;
    HttpClientRequestArgsAddr::HttpClientRequestArgs += bootloaderBase;
}

void HttpClientRequestArgs::addHeader(const char *key, const char *value) {
    return reinterpret_cast<void (*)(char*,const char*,const char*)>
    (HttpClientRequestArgsAddr::AddHeader)(args,key,value);
}

void HttpClientRequestArgs::initArgs(uint32_t type, const char *body, uint32_t bodyLen) {
    reinterpret_cast<void (*)(char*,uint32_t,const char*, uint32_t)>
    (HttpClientRequestArgsAddr::HttpClientRequestArgs)(args,type,body,bodyLen);
}

void HttpClientRequestArgs::clear() {
    memset(args,0,1600);
}
