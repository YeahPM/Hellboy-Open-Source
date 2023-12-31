//
// Created by 93261 on 2022/10/6.
//

#ifndef USERLIB_HTTPCLIENTREQUESTARGS_H
#define USERLIB_HTTPCLIENTREQUESTARGS_H

#include <cstdint>

void initHttpClientRequestArgsAddr(uint64_t bootloaderBase);

class HttpClientRequestArgs {
private:
    char args[1600];
public:
    void addHeader(const char* key, const char* value);
    void initArgs(uint32_t type, const char* body, uint32_t bodyLen);
    void clear();
};


#endif //USERLIB_HTTPCLIENTREQUESTARGS_H
