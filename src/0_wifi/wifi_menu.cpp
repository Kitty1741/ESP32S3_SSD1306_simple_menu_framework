#include <menu_API.h>

#include "connection/connection.h"

#include "wifi.h"


CREATE_MENU(WiFi,{
    {"状态",do_nothing,NULL},
    {"连接",run_node,&connection_menu_node},
})
CREATE_NODE(WiFi_menu)