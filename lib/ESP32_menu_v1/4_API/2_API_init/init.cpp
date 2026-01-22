#include <arduino.h>

#include "init.h"

//下层函数
#include "0_config/config.h"//宏
#include "1_driver/driver.h"
#include "2_engine/engine.h"
#include "3_display/display.h"

// init.cpp
init_node* init_list_head = NULL;

//宏定义函数 初始化
void system_init() {
    init_node* current = init_list_head;
    while (current) {
        current->init_func();  // 执行初始化
        current = current->next;
    }
}

//执行所有初始化函数的函数
void menu_API_init(){

    //debug
    #if( IF_DEBUG == true )
    Serial.begin(115200);
    #endif

    INIT_LIST_0
    INIT_LIST_1
    INIT_LIST_2
    INIT_LIST_3

    system_init();
}