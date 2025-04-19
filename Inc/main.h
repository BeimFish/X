#include"core.h"
#include"manager.h"
#include"Memory.h"
//#include"dispatch.h"
#include"datastruct/taskList.h"
#include"datastruct/memoryList.h"


#if defined(USE_WINDOWS)||defined(USE_LINUX)
Manager manager;
//Dispatcher dispatcher;
#else
#define manager (*((Manager*)(0x38000000)))

#endif

