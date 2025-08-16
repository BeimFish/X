#include"type.h"

class core;
class resList;



struct taskEntry
{
	taskEntry* next;
	void(*ptr)(core*);    //挂载待执行任务
	resList* res;         //挂载执行所需资源
	_u32 id;              //任务id

};

class taskList
{
	taskEntry start;
public:
	void init(_u32 id);
	void createEntry(taskEntry& newEntry);
	void deleteEntry(_u32 id);
	taskEntry& move();
	taskEntry& exec(_u32& tid);

	_ptrSize listLength();

};


