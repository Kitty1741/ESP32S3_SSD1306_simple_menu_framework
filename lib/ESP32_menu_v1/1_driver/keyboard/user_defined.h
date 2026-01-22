//这里声明用户的自定义函数


//把你自己的单次键盘扫描函数放在这里                 |
//这里的函数由你自己调用，if你不用也可以空着         |
//只要你的扫描-传值函数正常工作就行了                ↓
int default_scan_once_function();

//把你自己的完整键盘 扫描-传值 函数放在这里  |
//这里的函数会定时被timer中断执行           ↓
void default_scan_function();

//把你自己的键盘初始化函数放在这|
//这里的函数会定时被setup()执行 ↓
void default_init_function();