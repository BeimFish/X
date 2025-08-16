#include"core.h"
#include"bitMap.h"
#include"resList.h"
#include"taskList.h"
#include"memoryList.h"

#if OS == 1
//Windows模式
#include<new>
#include<thread>
#include<mutex>
#elif OS == 2 
//LINUX模式
#else
//未启用OS(系统)模式
#endif

#if NONE ==1
//CORTEX-M4模式
#elif NONE == 2 
//CORTEX-M7模式
#else
//未启用NONE(裸机)模式
#endif


void core::init(_u8 cid, void* ptr, _u32 size)
{
	this->cid = cid;
	//分配内核id
	this->pid = cid << 24;
	//生成0进程id（当前执行进程）
	execTaskNum = 1;
	//初始化pid生成器

	((memoryList*)memoryManager)->init(ptr, size, this->pid);
	//初始化内存管理


	taskManager = (taskList*)malloc(sizeof(taskList));
	//进程管理实例化


	taskManager->init(this->cid);
	//初始化进程管理


}
/*
* 内核初始化，需提供cid(内核id)，ptr(堆内存起始)，size(堆内存大小)
*/

_u8 core::create(void(*ptr)(core*), void* res)
{
	taskEntry* task = (taskEntry*)this->malloc(sizeof(taskEntry));
	//申请新进程块内存
	task->next = nullptr;
	//设置新进程块next指针为nullptr
	task->ptr = ptr;
	//挂载任务至新进程块
	task->res = (resList*)res;
	//资源表挂载
	if (execTaskNum == 0x000fffff)execTaskNum = 1;                             
	//任务计数超过最大值后重启计数
	task->id = (this->cid << 24) + execTaskNum++;
	//生成进程id
	taskManager->createEntry(*task);
	//在内核进程链表中创建进程
	return 0;
}
/*
* 进程创建
* ptr:待执行进程
* res:资源表
*/

_u32 core::ACPT()
{
	return pid;
}
/*
* 获取该内核当前执行进程的id
*/

_u32 core::taskLength()
{
	return taskManager->listLength();
}
/*
* 获取该内核待执行进程数
*/

void* core::malloc(_u32 size, _u8 token)
{
	return ((memoryList*)memoryManager)->createEntry(size, pid, token);
}
/*
* 内存申请，token默认为0(非共享内存)
*/

void core::free(void* ptr)
{
	((memoryList*)memoryManager)->deleteEntry(ptr);
}
void core::free(_u32 pid)
{
	((memoryList*)memoryManager)->deleteEntry(pid);
}
/*
* 内存释放
*/

void* core::getShare(_u8 token)
{
	return ((memoryList*)memoryManager)->getShare(token);
}
/*
* 获取已存在的共享内存
*/

void core::exec()
{
#if OS == 1
	//Windows模式
	auto start = [this]()
		{//内核0进程（空进程）
			taskEntry* execptr;
			//暂存待执行进程块
			for (;;)
			{


				execptr = &taskManager->exec(pid);
				//取出待执行进程块，切换执行进程id
				execptr->ptr(this);
				//执行该进程
				if (pid != (_u32)(this->cid << 24))
				{
					//执行进程不是0进程时，进入该分支
					free(execptr);
					//回收进程块所占内存
					free(pid);
					//回收结束进程的未回收内存
				}


				pid = this->cid << 24;
				//切换执行进程id至0进程

		}
};

	thread = new (((memoryList*)memoryManager)->createEntry(sizeof(std::thread), pid)) std::thread(start);
	//为线程分配内存，模拟硬件内核
#elif OS == 2 
	//LINUX模式
#else
	//未启用OS(系统)模式
#endif
#if NONE != 0

	taskEntry* execptr;
	//暂存待执行进程块
	execptr = &taskManager->exec(pid);
	//取出待执行进程块，切换执行进程id
	execptr->ptr(this);
	//执行该进程
	if (pid != (this->cid << 24))
	{
		//执行进程不是0进程时，进入该分支
		free(execptr);
		//回收进程块所占内存
		free(pid);
		//回收结束进程的未回收内存
	}
	pid = this->cid << 24;
	//切换执行进程id至0进程

#else
//未启用NONE(裸机)模式
#endif
}
/*
* 内核执行
* 该函数用于在所有配置结束后，拉起内核开始执行工作
*/
