#include "manager.h"
#include"datastruct/bitMap.h"
#include"datastruct/resList.h"
#include"datastruct/taskList.h"
#if defined(USE_WINDOWS) || defined(USE_LINUX)
#include<mutex>
#include<stdlib.h>
#else

#endif

void Manager::init()
{
	id = 1;

	size = HEAPSIZE;
	ptr = malloc(size);
	size = (_u32)ptr + HEAPSIZE;
	

}

