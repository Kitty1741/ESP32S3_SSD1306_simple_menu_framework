#ifndef __CREATE_NODE_MACRO_H__
#define __CREATE_NODE_MACRO_H__

//定义了快速创建m_ui_node_t类型的宏

#include <Arduino.h>
#include "3_display/1_u8g2_print/u8g2_print_struct.h"
#include "3_display/2_set_node/set_node.h"
#include "3_display/3_to_node/to_node.h"

#define GET_FIRST_ARG( _A0_ , ... ) _A0_
#define GET_ANOTHER_ARG( _B0_ , ... ) __VA_ARGS__

#define CREATE_NODE( DATA , ... )                       \
m_ui_node_t DATA##_node = to_node(                      \
    &DATA                                               \
    ,##__VA_ARGS__                                      \
);                                                      \

//eg.
/*
CREATE_MENU(test,{
    {"test",do_nothing},
})
CREATE_NODE(test_menu)
这样就创建了个菜单node
也可以
CREATE_IMAGE(test,8,{
    {0xff,0xff,0xff,0xff}
})
CREATE_NODE(test_image,8,8)
后面两个数字是坐标
*/

#endif