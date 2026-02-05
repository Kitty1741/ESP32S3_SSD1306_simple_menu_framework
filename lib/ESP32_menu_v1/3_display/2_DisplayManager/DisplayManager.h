#ifndef __DISPLAYMANAGER_H__
#define __DISPLAYMANAGER_H__

#include "3_display/display_struct.h"

void DisplayManager_init();

bool display_set( m_ui_node_t* node );
void display_refresh();

//u8g2多线程防卡死，给用户互斥锁接口
bool TakeDisplayMutex();
void GiveDisplayMutex();
//宏   将你的显示代码放到宏里，防止u8g2出错
#define M_DISPLAY(...)      \
    TakeDisplayMutex();     \
    u8g2.clearBuffer();     \
    __VA_ARGS__             \
    u8g2.sendBuffer();      \
    GiveDisplayMutex();     \
//eg.
/*
DISPLAY(

    u8g2.drawUTF8( 0 ,0 ,"你好世界");

)
*/

#endif