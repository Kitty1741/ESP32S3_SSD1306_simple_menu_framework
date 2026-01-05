#include <menu_API.h>
#include <WLAN/WLAN.h>

//这个文件专门用来定义主菜单

extern display_info TEST_MENU_INFO;
extern display_info TEST_LIST_INFO;
extern option TEST_MENU_LIST[];
extern menu TEST_MENU;
extern list TEST_LIST;

/*菜单选项格式如下*/
/*选项名(数组)*///*回调函数*///*传入参数(没有可以不写)*/
//主菜单选项列表
option MAIN_MENU_LIST[] = {
    {"WLAN",do_nothing},
    {"test",do_nothing},
    {"中文测试",do_nothing},
    {"回调函数-列表测试",run_info,&TEST_LIST_INFO},
    {"回调函数-菜单测试",run_info,&TEST_MENU_INFO},
    {"多行测试",do_nothing},
    {"多行测试",do_nothing},
};
//主菜单
menu MAIN_MENU = {
    /*标题*/.name = "主菜单",
    /*长度*/.length = sizeof(MAIN_MENU_LIST)/sizeof(MAIN_MENU_LIST[0]),
    /*选项列表*/.menu_list = MAIN_MENU_LIST,
};
char test_str[12];
list TEST_LIST = {
    .list = {
        [0] = "test_text" ,
        [1] = "中文测试" ,
        [2] = "中文测试" ,
        [3] = "中文测试" ,
        [4] = "中文测试" ,
        [5] = "test_text" ,
        [6] = "中文测试" ,
    }
};
option TEST_MENU_LIST[] = {
    {"回调函数-列表测试",run_info,&TEST_LIST_INFO},
};
menu TEST_MENU = {
    /*标题*/.name = "TEST",
    /*长度*/.length = sizeof(TEST_MENU_LIST)/sizeof(TEST_MENU_LIST[0]),
    /*选项列表*/.menu_list = TEST_MENU_LIST,
};

//对应显示包
display_info MAIN_MENU_INFO = menu_to_display_info( &MAIN_MENU );
display_info TEST_LIST_INFO = list_to_display_info( &TEST_LIST );
display_info TEST_MENU_INFO = menu_to_display_info( &TEST_MENU );