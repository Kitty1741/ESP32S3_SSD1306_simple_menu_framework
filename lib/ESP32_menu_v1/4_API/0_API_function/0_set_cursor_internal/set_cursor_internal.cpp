#include <Arduino.h>

#include "2_engine/engine.h"

#include "set_cursor_internal.h"


/*
    函数名字：set_cursor（重载4）
    函数功能：读取键值，设置光标
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        INFO
        类型：m_ui_node_t*
        作用：引入需要设置的菜单/列表
    或者
        MENU
        类型：menu*
        作用：作为参数引入需要设置的菜单
    或者
        LIST
        类型：list*
        作用：作为参数引入需要设置的列表
    或者
        SET
        类型：setting*
        作用：作为参数引入需要设置的列表
*///
bool set_cursor( m_ui_node_t* node ){
    switch ( node->type ){
    case UI_TYPE_LIST  : return set_cursor( node->data.list );
    case UI_TYPE_MENU  : return set_cursor( node->data.menu );
    case UI_TYPE_SETTING:return set_cursor( node->data.setting );
    default : break ;
    }return true;
}
bool set_cursor( m_menu_t* MENU ){ 
    return set_menu_cursor( MENU ); 
}
bool set_cursor( m_list_t* LIST ){ 
    return set_list_cursor( LIST ); 
}
bool set_cursor( m_setting_t* SET ){
    switch( SET->mode ){
        case SETTING_MODE_DOUBLE:return set_double_setting( SET );
        case SETTING_MODE_INT:return set_int_setting( SET );
        case SETTING_MODE_UCHAR:return set_uchar_setting( SET );
    }return true;
}