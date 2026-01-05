#include <Arduino.h>
#include <global.h>
#include <menu/menu.h>
#include <display/u8g2_print.h>
#include <API_function/API_function.h>

//本文件用于存放API提供的常用函数
//最有用包装最深的功能都在这了



/*
    函数名字：config_menu_display_info
    函数功能：用来把菜单转化为打印信息
    返回值：
      类型：display_info
      意义：包含一个菜单的打印信息
    参数：
      MENU
      类型：menu*
      作用：提供要配置的菜单的指针
*///
display_info menu_to_display_info(menu *MENU){
  
    display_info INFO;

    INFO.data.menu_t = MENU;
    INFO.mode = DISPLAY_MODE_MENU;
    INFO.next = NULL;

    return INFO;
}


/*
    函数名字：config_list_display_info
    函数功能：用来把列表转化为打印信息
    返回值：
      类型：display_info
      意义：包含一个列表的打印信息
    参数：
      LIST
      类型：list*
      作用：提供要配置的列表的指针
*///
display_info list_to_display_info(list *LIST){
  
    display_info INFO;

    INFO.data.list_t = LIST;
    INFO.mode = DISPLAY_MODE_LIST;
    INFO.next = NULL;
    INFO.x = 0;
    INFO.y = 0;

    return INFO;
}


/*
    函数名字：image_to_display_info
    函数功能：把128x64的char图片数组塞进一个display_info类型的结构里
    返回值：
        类型：display_info
        意义：返回需要渲染的图片的打印信息
    参数：
        IMAGE
        类型：char[1024]
        作用：传输需要打印的图片
*///
display_info image_to_display_info( char IMAGE[1024] ){

    display_info image_info;
    image_info.mode = DISPLAY_MODE_IMAGE;//图片打印模式
    strcpy(image_info.data.img->image_data , IMAGE );//给display_info赋值
    return image_info;
}


/*
    函数名字：do_nothing
    函数功能：菜单的回调函数,防止报空指针填的选项
    返回值：没有
    参数：没有
*///
bool do_nothing( void* do_nothing ){
    return true;
}
