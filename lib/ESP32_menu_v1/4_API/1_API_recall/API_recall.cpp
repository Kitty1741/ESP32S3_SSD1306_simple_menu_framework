#include <Arduino.h>

#include "API_recall.h"

//这里专门用来放包装好的常用回调函数


/*
    函数名字：run_node
    函数功能：循环运行info里的结构并且显示
    返回值：
        类型：bool
        意义：是否退出循环回调
    参数：
        INFO
        类型：m_ui_node_t*
        作用：提供运行节点的信息
*///
bool run_node( void* param ){

    m_ui_node_t* node = (m_ui_node_t*)param;
    bool return_value = false;

        switch( node->type ){//运行结构
        case UI_TYPE_MENU   :{
            return_value = set_cursor( node->data.menu );
        }break;// 菜单显示
        case UI_TYPE_LIST   :{
            return_value = set_cursor( node->data.list );
        }break;// 文字列表
        case UI_TYPE_SETTING:{
            return_value = set_cursor( node->data.setting );
        }break;
        default:if(get_last_key() == KEY_BACK_NUM)return true;break;
    }

    display_set( node );
    display_refresh();
    return return_value;
}


/*
    函数名字：do_nothing
    函数功能：菜单的回调函数,防止报空指针填的选项
    返回值：
        类型：bool
        意义：是否退出循环回调
    参数：没有
*///
bool do_nothing( void* do_nothing ){
    return true;
}
