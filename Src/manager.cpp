#include "manager.h"
#include"datastruct/bitMap.h"
#include"datastruct/resList.h"
#include"datastruct/taskList.h"
#include"datastruct/memoryList.h"
#if defined(USE_WINDOWS) || defined(USE_LINUX)
#include<mutex>
#include<stdlib.h>
#else

#endif

void Manager::init()
{
	id = 1;
	
	((memoryList*)memory)->init(HEAPSTART, HEAPSIZE, 0);

	

}
void* Manager::creatMemory(_u32 size,_u32 id)
{
	return ((memoryList*)memory)->createEntry(size, id);

}
void Manager::deleteMemory(void* sptr)
{
	((memoryList*)memory)->deleteEntry(sptr);
}
