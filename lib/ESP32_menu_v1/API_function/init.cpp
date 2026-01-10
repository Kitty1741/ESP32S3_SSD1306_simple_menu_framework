
// init.cpp
#include <arduino.h>
#include "init.h"


init_node* init_list_head = NULL;

void system_init() {
    init_node* current = init_list_head;
    while (current) {
        current->init_func();  // 执行初始化
        current = current->next;
    }
}