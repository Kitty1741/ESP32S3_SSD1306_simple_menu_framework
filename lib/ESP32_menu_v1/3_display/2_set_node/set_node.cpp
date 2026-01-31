#include <Arduino.h>

#include "3_display/1_u8g2_print/u8g2_print_struct.h"

#include "set_node.h"

/*
    函数名字：node_link
    函数功能：把后一个输入的指针追加到A所在的链表中，实现图层叠加
    返回值：
        类型：bool
        意义：返回是否设置成功，是则true
    参数：
        A
        类型：m_ui_node_t*
        作用：指向需要打印链表中的一个node的地址
        B
        类型：m_ui_node_t*
        作用：指向需要追加的node的地址
*///
void node_link(m_ui_node_t* A,m_ui_node_t* B){
    
    if( A == NULL || B == NULL )return;

    m_ui_node_t* ptr = A;
    while(1){
        if( ptr->next != NULL )
        ptr = ptr->next;
        else
        break;
    }

    ptr->next = B;
}

/*
    函数名字：node_init(重载2)
    函数功能：初始化一个node
    返回值：
        类型：m_ui_node_t
        意义：返回初始化的node，方便在进入函数前赋值
    参数：
        node
        类型：m_ui_node_t*
        作用：指向需要初始化的node的地址
      或者
        node
        类型：m_ui_node_t*
        作用：指向需要初始化的node的地址
        x
        类型：uint8_t
        作用：设置横坐标
        y
        类型：uint8_t
        用：设置纵坐标
*///
void node_init( m_ui_node_t* node ){
    if(node==NULL||node==nullptr)return;
    node->type = UI_TYPE_NONE;
    node->next = NULL;
    node->x = 0;
    node->y = 0;
}
void node_init( m_ui_node_t* node , uint8_t x , uint8_t y ){
    if(node==NULL||node==nullptr)return;
    node->type = UI_TYPE_NONE;
    node->next = NULL;
    node->x = x;
    node->y = y;
}

/*
    函数名字：node_set_xy
    函数功能：初始化一个node
    返回值：
        类型：bool
        意义：返回是否设置成功，是则true
    参数：
        node
        类型：m_ui_node_t*
        作用：指向需要初始化的node的地址
        x
        类型：uint8_t
        作用：设置横坐标
        y
        类型：uint8_t
        用：设置纵坐标
*///
void node_set_xy( m_ui_node_t* node , uint8_t x ,uint8_t y ){
    if(node==NULL||node==nullptr)return;
    node->x = x;
    node->y = y;
}