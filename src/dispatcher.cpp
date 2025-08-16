#include "dispatcher.h"
#include "bitMap.h"
#include "resList.h"
#include "taskList.h"
#include "memoryList.h"
#include "core.h"

#if OS == 1
// Windows模式
#include <stdlib.h>
#elif OS == 2
// LINUX模式
#else
#include "soures.h"
// 未启用OS(系统)模式
#endif

#if NONE == 1
// CORTEX-M4模式
#elif NONE == 2
// CORTEX-M7模式
#else
// 未启用NONE(裸机)模式
#endif

void dispatcher::init()
{
	this->id = 0;
	// 分配唯一的属于dispatcher的id
	execIdNum = 1;
	// 初始化pid生成器

#if HEAPSTART
	((memoryList *)memoryManager)->init(malloc(HEAPSIZE), HEAPSIZE, 0);
	// 初始化总堆内存
#else
	((memoryList *)memoryManager)->init((void *)address::heap, HEAPSIZE, 0);
	// 初始化内存管理
#endif // HEAPSTART

#if OS == 1
	// Windows模式
	c = (core *)((memoryList *)memoryManager)->createEntry(CORENUM * sizeof(core), id);
	// 分配内核地址
#elif NONE != 0
	// 裸机模式
	c = (core *)address::share;
#endif

	for (_u16 t = 0; t < CORENUM; t++)
	{
		c[t].init(t + 1, ((memoryList *)memoryManager)->createEntry(COREMEMORYSIZE, id), COREMEMORYSIZE);
		// 内核初始化
	}

	taskManager = (taskList *)((memoryList *)memoryManager)->createEntry(sizeof(taskList), id);
	// 进程管理实例化
	taskManager->init(id);
	// 初始化进程管理

	//((memoryList*)memoryManager)->createEntry(1024, id, 1);
	// 跨内核通讯管道
}

void dispatcher::create(void (*ptr)(core *), void *res)
{

	coreDispatchNum = 0;

	c[coreDispatchNum % CORENUM].create(ptr, res);
	coreDispatchNum++;
}

void dispatcher::exec()
{

#if OS != 0
	for (_u16 t = 0; t < CORENUM; t++)
		c[t].exec();
	for (;;)
		;
	// 开启调度器
#elif NONE != 0
	for (;;)
		for (_u16 t = 0; t < CORENUM; t++)
			c[t].exec();
	// 开启调度器
#endif
}
