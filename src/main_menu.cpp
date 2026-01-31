

#include "menu_API.h"

#include "test/test.h"

//这个文件专门用来定义主菜单


//主菜单选项列表
CREATE_MENU(main,{
    {"test",run_node,&test_menu_node},
    {"中文测试",do_nothing},
    {"回调函数-菜单测试",run_node,NULL},
    {"多行测试_01",do_nothing},
    {"多行测试_AB",do_nothing},
    {"多行测试_1B",do_nothing},
    {"多行测试_2B",do_nothing},
    {"多行测试_4B",do_nothing},
    {"多行测试_A8",do_nothing},
    {"多行测试_78",do_nothing},
    {"多行测试_91",do_nothing},
})
//对应显示包
m_ui_node_t main_menu_node = to_node( &main_menu );