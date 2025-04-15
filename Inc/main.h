#include"core.h"
#include"manager.h"
#include"messenger.h"

#include"datastruct/taskList.h"


#if defined(USE_WINDOWS)||defined(USE_LINUX)
Manager manager;
Messenger messenger;
#else
//#define messenger ((Messenger*)(0x38000000))
//#define manager ((Manager*)((_u8*)messenger + sizeof(Messenger)))
#endif

