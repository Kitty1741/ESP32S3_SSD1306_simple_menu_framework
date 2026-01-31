#ifndef __DISPLAYMANAGER_INTERNAL_H__
#define __DISPLAYMANAGER_INTERNAL_H__

//该文件只允许3_层调用

#include "3_display/display_struct.h"

//打印调用的m_ui_node_t变量指针
extern m_ui_node_t* PRINT_INFO;

//freeRTOS调用显示变量
extern SemaphoreHandle_t DisplayMutex;//显示互斥锁
extern QueueHandle_t  DisplayUpdateSem;//显示刷新信号
extern TaskHandle_t DisplayTask;//显示任务

#endif