#include <Arduino.h>

#include "API_recall.h"

//这里专门用来放包装好的常用回调函数


/*
    函数名字：run_info
    函数功能：显示内容。如果内容为菜单/列表就顺便检测按键并更改菜单/列表
    返回值：
        类型：bool
        意义：是否退出循环回调
    参数：
        param
        类型：void*
        作用：指向一个display_info，
*///
bool run_info(void* param){

    display_info* INFO = (display_info*)param;
    bool return_value = false;

        switch( INFO->mode ){//根据模式选择是否特调参数
        case DISPLAY_MODE_MENU   :{
            return_value = set_cursor( INFO->data.menu_t );
        }break;// 菜单显示
        case DISPLAY_MODE_LIST   :{
            return_value = set_cursor( INFO->data.list_t );
        }break;// 文字列表
        default:if(get_last_key() == KEY_BACK_NUM)return true;break;
    }

    display_set( INFO );
    display_refresh();
    return return_value;
}

/*
    函数名字：run_menu
    函数功能：简单地进入菜单
    返回值：
        类型：bool
        意义：是否退出循环回调
    参数：
        param
        类型：void*
        作用：指向一个 menu 结构体，用来确定进入哪个菜单
*///
bool run_menu(void* param){

    static display_info MENU_INFO;
    static menu* MENU;
    MENU = (menu*)param;
    
    if(set_menu_cursor( MENU ))return true;
    MENU_INFO = to_display_info( MENU );
    display_set( &MENU_INFO );
    display_refresh();
    return false;
}

/*
    函数名字：run_list
    函数功能：简单地进入列表
    返回值：
        类型：bool
        意义：是否退出循环回调
    参数：
        param
        类型：void*
        作用：指向一个 list 结构体，用来确定进入哪个列表
*///
bool run_list(void* param){

    static display_info LIST_INFO;
    static list *LIST;
    LIST = (list*)param;
    
    if(set_list_cursor( LIST ))return true;
    LIST_INFO = to_display_info( LIST );
    display_set( &LIST_INFO );
    display_refresh();
    return false;
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
