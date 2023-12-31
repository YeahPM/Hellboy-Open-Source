#pragma once

#include <jni.h>
#include <android/log.h>

enum LogType {
    oDEBUG = 3,
    oERROR = 6,
    oINFO  = 4,
    oWARN  = 5
};

#define TAG "Cipher"
#define TAG_HELLBOY "Hellboy"
#define TAG_HOOKS "HB-HOOKS"
#define TAG_TEXTURE "Texture"
#define TAG_MEMSCAN "HB-MEMSCAN"

#ifdef RELEASE_MODE
#define LOGD(...) 1
#define LOGE(...) 1
#define LOGI(...) 1
#define LOGW(...) 1
#else
#define LOGD(...) ((void)__android_log_print(oDEBUG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(oERROR, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(oINFO,  __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(oWARN,  __VA_ARGS__))
#endif


