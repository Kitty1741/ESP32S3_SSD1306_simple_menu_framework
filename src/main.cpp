#include <Arduino.h>
#include <menu_API.h>

extern m_ui_node_t main_menu_node;

void setup() {

    //menu_API
    menu_init();
}
void loop(){
    //主菜单
    run_node( &main_menu_node );
}
