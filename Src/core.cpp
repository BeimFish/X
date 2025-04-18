#include"core.h"
#include"datastruct/bitMap.h"
#include"datastruct/resList.h"
#include"datastruct/taskList.h"
#include"datastruct/memoryList.h"

#if defined(USE_CM4)||defined(USE_CM7)
#include"res/static/arm/cm_id.h"
#endif

#if defined(USE_WINDOWS) || defined(USE_LINUX)
#include<thread>
#include<mutex>
#endif

void Core::init(_u8 id, void* ptr, _u32 size)
{
	this->id = id;
	this->tid = id;
	execTaskNum = 1;

	((memoryList*)memoryManager)->init(ptr, size, id);


	resManager = (resList*)malloc(sizeof(resList));
	taskManager = (taskList*)malloc(sizeof(taskList));


	resManager->init(id);
	taskManager->init(id);



	auto start = [this]()
		{
			taskEntry* execptr;
			for (;;)
			{
				execptr = &taskManager->exec(tid);

				execptr->ptr(this);                //执行任务
				if (tid != (this->id << 24))
				{
					free(execptr);                 //释放任务块内存
					free(tid);                     //释放任务内存
				}
				tid = this->id;                    //进入主任务
			}
		};

#if defined(USE_WINDOWS) || defined(USE_LINUX)
	//thread = new std::thread(start);

	thread = new(((memoryList*)memoryManager)->createEntry(sizeof(std::thread), id))std::thread(start);
	




#else
	for(;;) start();
#endif


}
_u8 Core::create(void(*ptr)(Core*), void* res)
{
	taskEntry* task = (taskEntry*)this->malloc(sizeof(taskEntry));
	task->next = nullptr;
	task->ptr = ptr;
	task->res = (resList*)res;

	task->id = (this->id << 24) + execTaskNum++;
	taskManager->createEntry(*task);
	return 0;
}
_u32 Core::TID()
{
	return tid;
}
_u32 Core::taskLength()
{
	return taskManager->listLength();
}


#if defined(USE_WINDOWS) || defined(USE_LINUX)
std::mutex* Core::mutex(_u8 taskId)
{
	return (std::mutex*)resManager->readEntry(taskId, resVector::mutex);
}
#else
MUTEX* Core::mutex(_u8 taskId)
{
	return (MUTEX*)resMessenger->readEntry(taskId, resVector::mutex);
}
#endif
void* Core::malloc(_u32 size)
{
	return ((memoryList*)memoryManager)->createEntry(size, tid);
}
void Core::free(void* ptr)
{
	((memoryList*)memoryManager)->deleteEntry(ptr);
}
void Core::free(_u32 id)
{
	((memoryList*)memoryManager)->deleteEntry(id);
}

