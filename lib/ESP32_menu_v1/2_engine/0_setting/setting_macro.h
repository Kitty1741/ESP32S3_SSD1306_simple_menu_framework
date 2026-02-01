//setting_macro.h
#ifndef __SETTING_MACRO_H__
#define __SETTING_MACRO_H__

//定义了创建设置项的宏

#include <Arduino.h>
#include "setting_struct.h"

#define GET_FIRST_ARG( _A0_ , ... ) _A0_
#define GET_ANOTHER_ARG( _B0_ , ... ) __VA_ARGS__

#define CREATE_SETTING(NAME,MODE,OBJECT, ... )                              \
m_setting_t NAME##_setting = {                                              \
    #NAME,                                                                  \
    MODE,                                                                   \
    OBJECT,                                                                 \
    ##__VA_ARGS__                                                           \
};

#endif