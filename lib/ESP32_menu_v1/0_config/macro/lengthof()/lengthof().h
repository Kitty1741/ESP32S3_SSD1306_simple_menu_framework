#ifndef __LENGTHOF_H__
#define __LENGTHOF_H__

#include <Arduino.h>

//设置获取 数组长度 的宏
#if __cplusplus >= 201703L
#define lengthof(ARRAY) std::size(ARRAY)
#else
#define lengthof(ARRAY) sizeof(ARRAY)/sizeof(ARRAY[0])
#endif

#endif