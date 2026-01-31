#ifndef __U8G2_PRINT_STRUCT_H__
#define __U8G2_PRINT_STRUCT_H__

#include <Arduino.h>
//下级结构声明
#include "2_engine/engine_struct.h"

/*  显示  */
/*
这里定义打印函数作为参数的结构
该结构内部包含了各种类型
*/
//固定的几种屏幕输出模式
typedef enum{
    UI_TYPE_NONE,      // 不显示
    UI_TYPE_LOADING,   // 加载中
    UI_TYPE_MENU,      // 菜单显示
    UI_TYPE_LIST,      // 文字列表
    UI_TYPE_IMAGE,     // 图片显示
    UI_TYPE_SETTING,   // 设置界面显示
}m_ui_type_t;

//存储数据的共用体
typedef union{
    m_menu_t* menu;//菜单类型
    m_image_t* image;//图片类型
    m_list_t* list;//列表类型
    m_setting_t* setting;//设置类型
}m_ui_data_t;

//用来传值打印内容的结构
typedef struct m_ui_node_t{
    m_ui_type_t type;//输出内容的类型
    m_ui_data_t data;//内含一个和类型对应的结构的指针(内含信息)
    uint8_t x;//在屏幕上的坐标
    uint8_t y;//（只对一部分选项生效）
    m_ui_node_t* next;//链表结构，方便叠加图层
}m_ui_node_t;

#endif