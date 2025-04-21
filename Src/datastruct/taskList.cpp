#include <datastruct/taskList.h>
void taskList::init(_u32 acpt)
{
	start.next = nullptr;
	start.res = nullptr;
	start.ptr = [](Core*) {};
	start.acpt = acpt;

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
void taskList::deleteEntry(_u32 acpt)
{
	taskEntry* ptr = &start, * tem;

	for (; ptr->next != nullptr;)
	{
		if (ptr->next->acpt == acpt)
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

taskEntry& taskList::exec(_u32& acpt)
{
	taskEntry* ptr = &start, * tem;

	for (; ptr->next != nullptr;)
	{
		if (ptr->next->next== nullptr)
		{
			tem = ptr->next;
			ptr->next = nullptr;
			start.res = (resList*)((_u32)start.res - 1);
			acpt = tem->acpt;

			//fptr = tem->ptr;

			return *tem;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	acpt = ptr->acpt;

	return start;
}