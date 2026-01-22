#ifndef __LIST_STRUCT_H__
#define __LIST_STRUCT_H__

/*    
  列表 LIST
*///----------------------------------------------------------

typedef struct list_t{

    const char *name;//列表的标题
    unsigned char cursor;//列表的光标位置
    const char *list[64];//列表选项内容（ptr）

}list;

#endif