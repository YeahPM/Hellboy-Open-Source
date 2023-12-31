//
// Created by 93261 on 2022/10/6.
//

#ifndef USERLIB_HTTPCLIENT_H
#define USERLIB_HTTPCLIENT_H

#include "HttpClientRequestArgs.h"

void initHttpClientAddr(uint64_t bootloaderBase);

struct Url{
private:
    char m_type[0x8];
    char m_host[0x80];
    char m_port[0x6];
    char m_path[0x100];
public:
    void setType(const char*);
    void setHost(const char*);
    void setPort(uint32_t);
    void setPath(const char*);

    const char* getType();
    const char* getHost();
    const char* getPort();
    const char* getPath();
};

typedef uint64_t HttpRequestHandle;

class HttpClient {
private:
    uint64_t pThis;
    static HttpClient* httpClient;
public:
    static HttpClient* getHttpClient(uint64_t* pGame);
    uint64_t getPtr();
    void setPtr(uint64_t ptr);
    HttpClient(uint64_t ptr);

    HttpRequestHandle request(Url *,HttpClientRequestArgs *);
    uint64_t getRequest(HttpRequestHandle);

};


#endif //USERLIB_HTTPCLIENT_H
