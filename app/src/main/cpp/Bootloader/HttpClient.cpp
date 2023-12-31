//
// Created by 93261 on 2022/10/6.
//

#include <cstring>
#include <cstdio>
#include "HttpClient.h"

namespace HttpClientAddr {
    uint64_t GetRequest = 0xCBF708; // HttpClient::GetRequest(__int64 a1, int a2)
    uint64_t Request = 0xCBF3E8;  //HttpClient::Request(HttpClient *this, const Net::Uri *s1, const HttpClientRequestArgs *a3)
}

void initHttpClientAddr(uint64_t bootloaderBase){
    HttpClientAddr::GetRequest += bootloaderBase;
    HttpClientAddr::Request += bootloaderBase;
}

void Url::setType(const char * type) {
    strcpy(m_type, type);
}
void Url::setHost(const char* host) {
    strcpy(m_host, host);
}
void Url::setPath(const char* path) {
    strcpy(m_path, path);
}
void Url::setPort(uint32_t port) {
    snprintf(m_port,6,"%u", port);
}
const char* Url::getType() {
    return m_type;
}
const char* Url::getHost() {
    return m_host;
}
const char* Url::getPath() {
    return m_path;
}
const char* Url::getPort() {
    return m_port;
}

HttpClient * HttpClient::httpClient = nullptr;

HttpClient* HttpClient::getHttpClient(uint64_t* pGame) {
    if(httpClient == nullptr) {
        httpClient = new HttpClient(pGame[0x6D]);
    } else {
        httpClient->setPtr(pGame[0x6D]);
    }
    return httpClient;
}

uint64_t HttpClient::getPtr() {
    return pThis;
}
void HttpClient::setPtr(uint64_t ptr) {
    pThis = ptr;
}
HttpClient::HttpClient(uint64_t ptr) {
    pThis = ptr;
}
HttpRequestHandle HttpClient::request(Url * url,HttpClientRequestArgs* args) {
    return reinterpret_cast<HttpRequestHandle (*)(uint64_t,Url*,HttpClientRequestArgs*)>
    (HttpClientAddr::Request)(pThis,url,args);
}
uint64_t HttpClient::getRequest(HttpRequestHandle handle) {
    return reinterpret_cast<uint64_t (*)(uint64_t,HttpRequestHandle)>
    (HttpClientAddr::GetRequest)(pThis,handle);
}
