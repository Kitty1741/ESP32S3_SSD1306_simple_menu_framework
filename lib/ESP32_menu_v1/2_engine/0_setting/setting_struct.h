#ifndef __SETTING_STRUCT_H__
#define __SETTING_STRUCT_H__

#include <Arduino.h>

//设置变量类型枚举
typedef enum setting_mode_t{

    SETTING_MODE_CHAR,
    SETTING_MODE_INT,
    SETTING_MODE_FLOAT,

}setting_mode;

//设置结构体
typedef struct setting_t{

    const char* name;        //界面标题
    const setting_mode MODE; //设置变量的类型
    void* object;            //设置的对象指针
    float_t min;             //最小值
    float_t max;             //最大值

}setting;

#endif