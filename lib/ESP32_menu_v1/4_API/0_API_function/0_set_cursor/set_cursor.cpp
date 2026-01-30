#include "set_cursor.h"


/*
    函数名字：set_cursor（重载4）
    函数功能：读取键值，设置光标
    返回值：
        类型：bool
        意义：返回是否按下退出,如果是返回true
    参数：
        INFO
        类型：display_info*
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
bool set_cursor( display_info* INFO ){
    switch ( INFO->mode ){
    case DISPLAY_MODE_LIST  : return set_cursor( INFO->data.list_t );
    case DISPLAY_MODE_MENU  : return set_cursor( INFO->data.menu_t );
    case DISPLAY_MODE_SETTING:return set_cursor( INFO->data.setting_t );
    default : break ;
    }return true;
}
bool set_cursor( m_menu_t* MENU )
{ return set_menu_cursor( MENU ); }
bool set_cursor( m_list_t* LIST )
{ return set_list_cursor( LIST ); }
bool set_cursor( m_setting_t* SET ){
    switch( SET->MODE ){
        case SETTING_MODE_DOUBLE:return set_double_setting( SET );
        case SETTING_MODE_INT:return set_int_setting( SET );
        case SETTING_MODE_CHAR:return set_char_setting( SET );
    }return true;
}