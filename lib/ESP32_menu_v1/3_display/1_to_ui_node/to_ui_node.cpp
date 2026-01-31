//to_ui_node.cpp
#include <Arduino.h>

#include "to_ui_node_private.h"
#include "to_ui_node.h"

//提供了一套重载函数，可以把m_ui_data_t里面定义的类型转化为m_ui_node_t


/*
    函数名字：to_node（重载5）
    函数功能：用来把低级结构转化为打印信息
    返回值：
      类型：m_ui_node_t
      意义：包含一个菜单的打印信息
    参数：
      MENU
      类型：menu*
      作用：提供要配置的菜单的指针
    或者
      LIST
      类型：list*
      作用：提供要配置的列表的指针
    或者
      IMAGE
      类型：image*
      作用：指向需要打印的图片的地址,从屏幕左上角开始打印
    或者
      IMAGE
      类型：image*
      作用：指向需要打印的图片的地址
      x
      类型：uint8_t
      作用：表示打印图片左上角的坐标
      y
      类型：uint8_t
      作用：表示打印图片左上角的坐标
      
*///
m_ui_node_t to_node(m_menu_t *MENU)
{return menu_to_node(MENU);}
m_ui_node_t to_node(m_list_t *LIST)
{return list_to_node(LIST);}
m_ui_node_t to_node( m_image_t* IMAGE )
{return image_to_node(IMAGE,0,0);}
m_ui_node_t to_node( m_image_t* IMAGE , uint8_t x , uint8_t y)
{return image_to_node(IMAGE,x,y);}
m_ui_node_t to_node(m_setting_t *SET)
{return setting_to_node(SET);}

/*
    函数名字：menu_to_ui_node
    函数功能：用来把菜单转化为打印信息
    返回值：
      类型：m_ui_node_t
      意义：包含一个菜单的打印信息
    参数：
      MENU
      类型：m_menu_t*
      作用：提供要配置的菜单的指针
*///
m_ui_node_t menu_to_node(m_menu_t *MENU){
  
    m_ui_node_t INFO;

    INFO.data.menu = MENU;
    INFO.type = UI_TYPE_MENU;
    INFO.next = NULL;

    return INFO;
}


/*
    函数名字：list_to_ui_node
    函数功能：用来把列表转化为打印信息
    返回值：
      类型：m_ui_node_t
      意义：包含一个列表的打印信息
    参数：
      LIST
      类型：m_list_t*
      作用：提供要配置的列表的指针
*///
m_ui_node_t list_to_node(m_list_t *LIST){
  
    m_ui_node_t INFO;

    INFO.data.list = LIST;
    INFO.type = UI_TYPE_LIST;
    INFO.next = NULL;
    INFO.x = 0;
    INFO.y = 0;

    return INFO;
}


/*
    函数名字：image_to_ui_node
    函数功能：把图片数组塞进一个m_ui_node_t类型的结构里
    返回值：
        类型：m_ui_node_t
        意义：返回需要渲染的图片的打印信息
    参数：
        IMAGE
        类型：m_image_t*
        作用：指向需要打印的图片的地址
        x
        类型：uint8_t
        作用：表示打印图片左上角的坐标
        y
        类型：uint8_t
        作用：表示打印图片左上角的坐标

*///
m_ui_node_t image_to_node( m_image_t* IMAGE , uint8_t x , uint8_t y ){
    
    // 设置坐标
    m_ui_node_t image_node;
    image_node.x = x;
    image_node.y = y;
    
    image_node.type = UI_TYPE_IMAGE;//图片打印模式
    image_node.data.image = IMAGE;
    image_node.next = NULL;
    return image_node;
}


/*
    函数名字：setting_to_ui_node
    函数功能：用来把菜单转化为打印信息
    返回值：
      类型：m_ui_node_t
      意义：包含一个菜单的打印信息
    参数：
      SET
      类型：m_setting_t*
      作用：提供要配置的菜单的指针
*///
m_ui_node_t setting_to_node(m_setting_t *SET){
  
    m_ui_node_t INFO;

    INFO.data.setting = SET;
    INFO.type = UI_TYPE_SETTING;
    INFO.next = NULL;

    return INFO;
}


/*
    函数名字：link_ui_node
    函数功能：把后一个输入的指针追加到A所在的链表中，实现图层叠加
    返回值：没有
    参数：
        A
        类型：m_ui_node_t*
        作用：指向需要打印链表中的一个node的地址
        B
        类型：m_ui_node_t*
        作用：指向需要追加的node的地址
*///
void link_node(m_ui_node_t* A,m_ui_node_t* B){
    
    if( A == nullptr || B == nullptr )
    return;

    m_ui_node_t* ptr = A;
    while(1){
        if( ptr->next != NULL )
        ptr = ptr->next;
        else
        break;
    }

    ptr->next = B;
}