//list_struct.h
#ifndef __LIST_STRUCT_H__
#define __LIST_STRUCT_H__

#include <Arduino.h>

//列表结构体
typedef struct{

    const char *name;//列表的标题
    uint16_t cursor;//列表的光标位置
    uint16_t length;//列表的长度
    const char**items;//列表选项内容（ptr）

}m_list_t;

#endif