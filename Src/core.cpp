#include"core.h"
#include"datastruct/bitMap.h"
#include"datastruct/resList.h"
#include"datastruct/taskList.h"

#if defined(USE_CM4)||defined(USE_CM7)
#include"res/static/arm/cm_id.h"
#endif

#if defined(USE_WINDOWS) || defined(USE_LINUX)
#include<thread>
#include<mutex>
#endif

void Core::init(_u8 id)
{
	this->id = id;
	execTaskNum = 1;

	resMessenger = new resList;
	taskMessenger = new taskList;


	resMessenger->init(id);
	taskMessenger->init(id);



	auto start = [this]()
		{

			for (;;)
			{
				taskMessenger->exec(tid)(this);
			}
		};

#if defined(USE_WINDOWS) || defined(USE_LINUX)
	thread = new std::thread(start);
#else
	for(;;) start();
#endif


}
_u8 Core::create(taskEntry& task)
{
	task.id = (this->id << 24) + execTaskNum++;
	taskMessenger->createEntry(task);
	return 0;
}
_u32 Core::TID()
{
	return tid;
}
_u32 Core::taskLength()
{
	return taskMessenger->listLength();
}


#if defined(USE_WINDOWS) || defined(USE_LINUX)
std::mutex* Core::mutex(_u8 taskId)
{
	return (std::mutex*)resMessenger->readEntry(taskId, resVector::mutex);
}
#else
MUTEX* Core::mutex(_u8 taskId)
{
	return (MUTEX*)resMessenger->readEntry(taskId, resVector::mutex);
}
#endif
