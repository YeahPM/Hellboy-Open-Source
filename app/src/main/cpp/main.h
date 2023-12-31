#pragma once
#include <pthread.h>


static pthread_t init_hellboy;
typedef void (*func)();
void Main();
void* Init(void*);


extern "C" func __attribute__((visibility ("default"))) Start()
{
    pthread_create(&init_hellboy, nullptr, Init, nullptr);
    pthread_detach(init_hellboy);
    return &Main;
}



