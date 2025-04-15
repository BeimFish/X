#include <datastruct/taskList.h>
void taskList::init(_u32 id)
{
	start.next = nullptr;
	start.res = (resList*)0;
	start.ptr = [](Core*) {};
	start.id = id;
}
void taskList::createEntry(taskEntry& newEntry)
{
	taskEntry* ptr = &newEntry;
	for (_u16 i = 1;; i++)
	{

		if (ptr->next == nullptr)
		{
			ptr->next = start.next;
			start.next = &newEntry;

			start.res = (resList*)((_u32)start.res + i);

			return;
		}
		else
		{
			ptr = ptr->next;
		}
	}
}
void taskList::deleteEntry(_u32 id)
{
	taskEntry* ptr = &start, * tem;

	for (; ptr->next != nullptr;)
	{
		if (ptr->next->id == id)
		{
			ptr->next = ptr->next->next;
			start.res = (resList*)((_u32)start.res - 1);
			return;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	return;
}
_u32 taskList::listLength()
{
	return (_u32)start.res;
}
taskEntry& taskList::move()
{
	taskEntry* ptr = &start, * tem;

	for (; ptr->next != nullptr;)
	{
		if (ptr->next->next == nullptr)
		{
			tem = ptr->next;
			ptr->next = nullptr;
			start.res = (resList*)((_u32)start.res - 1);


			return *tem;
		}
		else
		{
			ptr = ptr->next;
		}
	}


	return start;
}




void (*taskList::exec(_u32& tid))(Core*)
{
	taskEntry* ptr = &start, * tem;

	for (; ptr->next != nullptr;)
	{
		if (ptr->next->next== nullptr)
		{
			tem = ptr->next;
			ptr->next = nullptr;
			start.res = (resList*)((_u32)start.res - 1);
			tid = tem->id;

			return tem->ptr;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	tid = ptr->id;

	return start.ptr;
}