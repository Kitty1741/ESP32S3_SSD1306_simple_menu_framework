//menu_struct.h
#ifndef __MENU_STRUCT_H__
#define __MENU_STRUCT_H__

#include <Arduino.h>

//菜单选项结构体
typedef struct{

    const char* name;          //选项名字
    void (*callback)(void*);//这里放回调函数指针和回调函数参数
    void* param;            //task_loop的参数

}m_option_t;

//菜单结构体
typedef struct{

    const char *name;//菜单的标题
    uint16_t cursor;//菜单的光标位置
    uint16_t length;//菜单的列表长度
    m_option_t *items;//菜单对应的选项列表

}m_menu_t;

#endif