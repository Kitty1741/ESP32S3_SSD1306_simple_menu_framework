#include <Arduino.h>

#include "API_recall.h"

//这里专门用来放包装好的常用回调函数


/*
    函数名字：run_node
    函数功能：循环运行info里的结构并且显示
    返回值：没有
    参数：
        INFO
        类型：m_ui_node_t*
        作用：提供运行节点的信息
*///
void run_node( void* param ){

    __DEBUG_4("run_node()\n")

    m_ui_node_t* node = (m_ui_node_t*)param;

while(1){
        switch( node->type ){//运行结构
        case UI_TYPE_MENU   :{
            if( set_cursor( node->data.menu ) )return;
        }break;// 菜单显示
        case UI_TYPE_LIST   :{
            if( set_cursor( node->data.list ) )return;
        }break;// 文字列表
        case UI_TYPE_SETTING:{
            if( set_cursor( node->data.setting ) )return;
        }break;
        default:if( get_first_key() == KEY_BACK_NUM )return;
    }

    display_set( node );
    display_refresh();
}}


/*
    函数名字：do_nothing
    函数功能：菜单的回调函数,防止报空指针填的选项
    返回值：
        类型：bool
        意义：是否退出循环回调
    参数：没有
*///
void do_nothing( void* do_nothing ){
    return;
}
