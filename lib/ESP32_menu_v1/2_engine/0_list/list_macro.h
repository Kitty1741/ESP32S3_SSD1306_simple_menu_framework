//list_macro.h
#ifndef __LIST_MACRO_H__
#define __LIST_MACRO_H__

//定义了快速创建列表的宏

#include "0_config/config.h"
#include "list_struct.h"

#define CREATE_LIST( NAME , ... )                       \
static const char* NAME##_list_items[] = __VA_ARGS__;   \
m_list_t NAME##_list = {                                \
    .name = #NAME,                                      \
    .cursor = 0,                                        \
    .length = lengthof(NAME##_list_items),              \
    .items = NAME##_list_items,                         \
};

//eg.
/*
CREATE_LIST( test ,{
    "hello world",
    "hi?",
    &strptr
})


意味着
创建一个叫 "test_list" 的列表 (列表名 = 输入名字 + _list)
并添加三个元素
第一个："hello world"
第二个："hi?"
第三个：strptr里的数据(必须是C字符串)
*/

#endif