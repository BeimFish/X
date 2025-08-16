#include "taskList.h"
void taskList::init(_u32 id)
{
	start.next = nullptr;
	//start指向空节点
	start.res = (resList*)0;
	//start节点的res用于记录当前内核待处理任务的数量
	start.ptr = [](core*) {};
	//默认空进程（0号进程）
	start.id = (id << 24);
	//生成0号进程的id(内核id<<24)
}
/*
* id:该内存管理的所属内核id
*/

void taskList::createEntry(taskEntry& newEntry)
{
	taskEntry* ptr = &newEntry;
	//指向需要被创建的进程块

	for (_u16 i = 1;; i++)
	{
		//计数器，计算添加进程块的长度


		if (ptr->next == nullptr)
		{
			//如果当前进程块后方无链接进程块，则进入该分支
			ptr->next = start.next;
			//将当前进程块的next指针指向第一个任务
			start.next = &newEntry;
			//start的next指针指向第一个新增添进程(ptr被多次移动，但newEntry永远是指向这段进程链的首个进程块)

			start.res = (resList*)((_ptrSize)start.res + i);
			//更新进程数量

			return;
		}
		else
		{
			//如果当前进程块后方有链接进程块，则进入该分支
			ptr = ptr->next;
			//ptr后移一位，重新判断
		}
	}
}
/*
* 创建进程块
* newEntry:新增的进程块（也可是进程块链）
*/

void taskList::deleteEntry(_u32 id)
{
	taskEntry* ptr = &start;
	//临时指针指向空进程

	for (; ptr->next != nullptr;)
	{
		//判断下一个进程块是否存在，存在则进入该分支
		if (ptr->next->id == id)
		{
			//检查下一个进程的id是否是所需删除的进程id，是则进入该分支

			ptr->next = ptr->next->next;
			//将下一个需要删除的进程删除
	


			start.res = (resList*)((_ptrSize)start.res - 1);
			//更新进程数量
			return;
		}
		else
		{
			//检查下一个进程的id是否是所需删除的进程id，不是则进入该分支
			ptr = ptr->next;
			//当前指向进程后移
		}
	}
	return;
}
/*
* 根据id删除对应的尚未执行的进程
*/

_ptrSize taskList::listLength()
{
	//返回start.res内容，此位记录了当前链表的长度（进程数）
	return (_ptrSize)start.res;
}
/*
* 返回进程链表的长度（待执行进程数量）
*/

taskEntry& taskList::move()
{
	taskEntry* ptr = &start, * tem;

	for (; ptr->next != nullptr;)
	{
		if (ptr->next->next == nullptr)
		{
			tem = ptr->next;
			ptr->next = nullptr;
			start.res = (resList*)((_ptrSize)start.res - 1);


			return *tem;
		}
		else
		{
			ptr = ptr->next;
		}
	}


	return start;
}

taskEntry& taskList::exec(_u32& tid)
{
	taskEntry* ptr = &start, * tem;
	//当前指向start进程
	for (; ptr->next != nullptr;)
	{
		//检查后方是否存在进程，存在则进入该循环

		if (ptr->next->next== nullptr)
		{
			//检查后方进程是否是最后一个进程，是则进入该分支
			tem = ptr->next;
			//临时保存最后一个进程的进程块
			ptr->next = nullptr;
			//清理当前进程的next指针
			start.res = (resList*)((_ptrSize)start.res - 1);
			//进程数减一
			tid = tem->id;
			//当前正在执行进程的id

			//fptr = tem->ptr;

			return *tem;
			//将该进程块送出
		}
		else
		{
			//检查后方进程是否是最后一个进程，不是则进入该分支
			ptr = ptr->next;
			//当前指向进程后移，重新检查
		}
	}

	tid = ptr->id;
	//start不存在后方进程块，将执行进程id设置为当前内核的0号进程id

	return start;
	//执行0进程
}
/*
* 在OS环境下，需手动调用exec启动调度器
* tid:链接core的tid，便于外部追踪执行进程
*/
