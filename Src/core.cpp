#include"core.h"
#include"datastruct/bitMap.h"
#include"datastruct/resList.h"
#include"datastruct/taskList.h"
#include"datastruct/memoryList.h"

#if defined(USE_CM4)||defined(USE_CM7)
#include"res/static/arm/cm_id.h"
#endif

#if defined(USE_WINDOWS)
#include<thread>
#include<mutex>
#endif

void Core::init(_u8 cid, void* ptr, _u32 size)
{
	this->cid = cid;
	this->acpt = cid << 24;                                       //ACPT不符
	execTaskNum = 1;

	((memoryList*)memoryManager)->init(ptr, size, this->acpt);


	resManager = (resList*)malloc(sizeof(resList));
	taskManager = (taskList*)malloc(sizeof(taskList));


	resManager->init(this->acpt);
	taskManager->init(this->acpt);


}
_u8 Core::create(void(*ptr)(Core*), void* res)
{
	taskEntry* task = (taskEntry*)this->malloc(sizeof(taskEntry));
	task->next = nullptr;
	task->ptr = ptr;
	task->res = (resList*)res;

	if (execTaskNum == 0x000fffff)execTaskNum = 0;                             //任务量过大重启

	task->acpt = (task->acpt & 0xf0000000) | (this->cid << 24) + (execTaskNum++ << 4);
	taskManager->createEntry(*task);
	return 0;
}
_u32 Core::ACPT()
{
	return acpt;
}
_u32 Core::taskLength()
{
	return taskManager->listLength();
}


#if defined(USE_WINDOWS)
std::mutex* Core::mutex(_u8 acpt)
{
	return (std::mutex*)resManager->readEntry(acpt, resVector::mutex);
}
#else
MUTEX* Core::mutex(_u8 taskId)
{
	//return (MUTEX*)resMessenger->readEntry(taskId, resVector::mutex);
	return nullptr;
}
#endif
void* Core::malloc(_u32 size)
{
	return ((memoryList*)memoryManager)->createEntry(size, acpt);
}
void Core::free(void* ptr)
{
	((memoryList*)memoryManager)->deleteEntry(ptr);
}
void Core::free(_u32 acpt)
{
	((memoryList*)memoryManager)->deleteEntry(acpt);
}

void Core::exec()
{
	auto start = [this]()
		{
			taskEntry* execptr;
			for (;;)
			{


				execptr = &taskManager->exec(acpt);

				execptr->ptr(this);                //ִ后期改进，taskEntry的Create和Delete均由dispatcher负责
				if (acpt != (this->cid << 24))
				{
					free(execptr);                 //�ͷ�������ڴ�
					free(acpt);                     //�ͷ������ڴ�
				}


				acpt = this->cid << 24;                    //����������

			}
		};

#if defined(USE_WINDOWS)
	//thread = new std::thread(start);

	thread = new(((memoryList*)memoryManager)->createEntry(sizeof(std::thread), acpt))std::thread(start);

#else
	for (;;) start();
#endif

}
