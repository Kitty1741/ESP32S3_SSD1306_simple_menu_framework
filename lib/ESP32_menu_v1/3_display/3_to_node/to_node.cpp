//to_ui_node.cpp
#include <Arduino.h>

#include "3_display/2_set_node/set_node.h"

#include "to_node_private.h"
#include "to_node.h"

//提供了一套重载函数，可以把m_ui_data_t里面定义的类型转化为m_ui_node_t


/*
    函数名字：to_node（重载8）
    函数功能：用来把低级结构转化为打印信息
    返回值：
      类型：m_ui_node_t
      意义：包含一个菜单的打印信息
    参数太多了，大致讲一下规则
      参数是m_menu_t*，m_list_t*，m_image_t* ，m_setting_t*中的任意类型之一即可
      如果是m_list_t*，m_image_t*还可以加两个参数x，y来指定打印位置
      
*///


m_ui_node_t to_node(m_setting_t *SET){return setting_to_node(SET);}
m_ui_node_t to_node(m_setting_t *SET,uint8_t x,uint8_t y){return setting_to_node(SET);}
m_ui_node_t to_node(m_menu_t *MENU){return menu_to_node(MENU);}
m_ui_node_t to_node(m_menu_t *MENU,uint8_t x,uint8_t y){return menu_to_node(MENU);}
m_ui_node_t to_node(m_list_t *LIST){return list_to_node(LIST,0,0);}
m_ui_node_t to_node(m_list_t *LIST,uint8_t x,uint8_t y){return list_to_node(LIST,x,y);}
m_ui_node_t to_node(m_image_t* IMAGE){return image_to_node(IMAGE,0,0);}
m_ui_node_t to_node(m_image_t* IMAGE,uint8_t x,uint8_t y){return image_to_node(IMAGE,x,y);}

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
    node_init(&INFO);

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
      x,y
      类型：uint8_t
      作用：提供打印坐标
*///
m_ui_node_t list_to_node(m_list_t *LIST,uint8_t x,uint8_t y){
  
    m_ui_node_t node;
    node_init(&node);

    node.data.list = LIST;
    node.type = UI_TYPE_LIST;
    node.next = NULL;
    node.x = x;
    node.y = y;

    return node;
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
        x,y
        类型：uint8_t
        作用：提供打印坐标

*///
m_ui_node_t image_to_node( m_image_t* IMAGE,uint8_t x,uint8_t y ){
    
    // 设置坐标
    m_ui_node_t node;
    node_init(&node);
    node.x = x;
    node.y = y;

    node.type = UI_TYPE_IMAGE;//图片打印模式
    node.data.image = IMAGE;
    node.next = NULL;
    return node;
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
  
    m_ui_node_t node;
    node_init(&node);

    node.data.setting = SET;
    node.type = UI_TYPE_SETTING;
    node.next = NULL;

    return node;
}