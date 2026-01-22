#include <Arduino.h>

#include "API_function.h"

//本文件用于存放API提供的常用函数
//最有用包装最深的功能都在这了

/*
    函数名字：menu_to_display_info
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
    函数名字：list_to_display_info
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
    函数功能：把图片数组塞进一个display_info类型的结构里
    返回值：
        类型：display_info
        意义：返回需要渲染的图片的打印信息
    参数：
        IMAGE
        类型：image*
        作用：指向需要打印的图片的地址
        可变参数
        描述：只能填两个uint8_t类型的数据，用来描述图片左上角的xy坐标
*///
display_info image_to_display_info( image* IMAGE , ... ){

    // 处理可变参数
    va_list args;
    va_start(args, IMAGE); // 初始化可变参数列表
    int x = va_arg(args, int);// 获取第一个参数（x坐标）
    int y = va_arg(args, int);// 获取第二个参数（y坐标）
    va_end(args); // 清理可变参数列表
    
    // 设置坐标
    display_info image_info;
    image_info.x = x;
    image_info.y = y;
    
    image_info.mode = DISPLAY_MODE_IMAGE;//图片打印模式
    image_info.data.img = IMAGE;
    return image_info;
}


/*
    函数名字：link_info
    函数功能：把后一个输入的指针追加到A所在的链表中，实现图层叠加
    返回值：没有
    参数：
        A
        类型：display_info*
        作用：指向需要打印链表中的一个info的地址
        B
        类型：display_info*
        作用：指向需要追加的info的地址
*///
void link_info(display_info* A,display_info* B){
    
    if( A == NULL || B == NULL )
    return;

    display_info* ptr = A;
    while(1){
        if( ptr->next != NULL )
        ptr = ptr->next;
        else
        break;
    }

    ptr->next = B;
}