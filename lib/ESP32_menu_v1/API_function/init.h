// init.h
#ifndef __INIT_H__
#define __INIT_H__

// 初始化函数链表节点
typedef struct init_node_t {
    void (*init_func)();          // 初始化函数指针
    struct init_node_t* next;        // 下一个节点
} init_node;

// 全局链表头
extern init_node* init_list_head;

// 注册宏（核心）
#define INIT(name) \
    __attribute__((constructor)) \
    static void _register_##name() { \
        extern void name##_init(); \
        static init_node_t node = {name##_init, NULL}; \
        node.next = init_list_head; \
        init_list_head = &node; \
    }

// 主初始化函数
void system_init();

#endif