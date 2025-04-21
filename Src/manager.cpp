#include "manager.h"
#include"datastruct/bitMap.h"
#include"datastruct/resList.h"
#include"datastruct/taskList.h"
#include"datastruct/memoryList.h"
#if defined(USE_WINDOWS)
#include<mutex>
#include<stdlib.h>
#else

#endif

void Manager::init()
{
	cid = 1;
	
	((memoryList*)memory)->init(HEAPSTART, HEAPSIZE, this->cid << 24);

	

}
void* Manager::creatMemory(_u32 size)
{
	return ((memoryList*)memory)->createEntry(size, cid << 24);

}
void Manager::deleteMemory(void* sptr)
{
	((memoryList*)memory)->deleteEntry(sptr);
}
