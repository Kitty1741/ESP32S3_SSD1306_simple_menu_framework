#ifndef __INIT_H__
#define __INIT_H__

// init.h

/*
这个模块声明了一个超级好用的宏
该宏可以用非常简单的语法
将自定义函数添加到初始化队列

语法就像这样
void XXX_init(){
    ......
}

INIT(XXX)    //必须要_init作为后缀,填写不带后缀

等同于
setup(){

    ......

    XXX_init();

}
*/





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

// 宏初始化函数
void system_init();

// 模块总初始化函数
void menu_API_init();

#endif