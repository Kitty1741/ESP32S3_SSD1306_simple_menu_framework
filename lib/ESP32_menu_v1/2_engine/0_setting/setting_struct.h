//setting_struct.h
#ifndef __SETTING_STRUCT_H__
#define __SETTING_STRUCT_H__

#include <Arduino.h>

//设置变量类型枚举
typedef enum{

    SETTING_MODE_UCHAR,
    SETTING_MODE_INT,
    SETTING_MODE_DOUBLE,

}m_setting_mode;

//设置结构体
typedef struct{

    const char* name;        //界面标题
    const m_setting_mode mode; //设置变量的类型
    void* object;            //设置的对象指针
    double_t min;             //最小值
    double_t max;             //最大值

}m_setting_t;

#endif