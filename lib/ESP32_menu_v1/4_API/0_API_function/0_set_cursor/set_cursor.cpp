#include "set_cursor.h"


/*
    函数名字：set_cursor（重载3）
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
*///
bool set_cursor( display_info* INFO ){
    switch ( INFO->mode ){
    case DISPLAY_MODE_LIST : return set_cursor( INFO->data.list_t );
    case DISPLAY_MODE_MENU : return set_cursor( INFO->data.menu_t );
    default : break ;
    }return true;
}
bool set_cursor( menu* MENU )
{ return set_menu_cursor( MENU ); }
bool set_cursor( list* LIST )
{ return set_list_cursor( LIST ); }