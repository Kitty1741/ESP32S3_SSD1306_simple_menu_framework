#include <Arduino.h>

#include "API_recall.h"

//这里专门用来放包装好的常用回调函数


/*
    函数名字：run_info
    函数功能：循环运行info里的结构并且显示
    返回值：
        类型：bool
        意义：是否退出循环回调
    参数：
        INFO
        类型：display_info*
        作用：指向一个display_info，
*///
bool run_info( void* param ){

    display_info* INFO = (display_info*)param;
    bool return_value = false;

        switch( INFO->mode ){//运行结构
        case DISPLAY_MODE_MENU   :{
            return_value = set_cursor( INFO->data.menu_t );
        }break;// 菜单显示
        case DISPLAY_MODE_LIST   :{
            return_value = set_cursor( INFO->data.list_t );
        }break;// 文字列表
        case DISPLAY_MODE_SETTING:{
            return_value = set_cursor( INFO->data.setting_t );
        }break;
        default:if(get_last_key() == KEY_BACK_NUM)return true;break;
    }

    display_set( INFO );
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
