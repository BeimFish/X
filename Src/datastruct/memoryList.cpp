#include"datastruct/memoryList.h"



void memoryList::init(void* sptr, _u32 size, _u32 id)
{

	start.next = &end;
	start.id = id;

	start.size = 0;                       
	start.sptr = (_ptrSize)sptr;                             //堆内存起始地址 


	end.next = nullptr;
	end.id = size;                                                      //当前内存块使用者ID

	end.size = 0;                                                     //当前内存块可用数据大小
	end.sptr = start.sptr + size + sizeof(memoryEntry);            //堆内存结束地址+sizeof(memoryEntry)



}
void* memoryList::createEntry(_u32 size,_u32 id)
{
	memoryEntry* ptr = &start;

	for (;;)
	{
		if ((size + sizeof(memoryEntry)) <= (ptr->next->sptr - sizeof(memoryEntry) - ptr->sptr - ptr->size))
		{



			memoryEntry* t = (memoryEntry*)(ptr->sptr + ptr->size);
			t->id = id;

			t->next = ptr->next;
			ptr->next = t;
		
			t->sptr = (_ptrSize)t + sizeof(memoryEntry);
			t->size = size;
			end.id = end.id - sizeof(memoryEntry) - size;
			return (void*)t->sptr;


		}
		else
		{
			if (ptr->next->next == nullptr) return nullptr;
			ptr = ptr->next;
		}
	}
}
void memoryList::deleteEntry(void* dptr)
{
	memoryEntry* ptr = &start;

	for (;;)
	{
		if (ptr->next->next != nullptr)
		{
			if (ptr->next->sptr == (_ptrSize)dptr)
			{
				end.id = end.id + sizeof(memoryEntry) + ptr->next->size;
				ptr->next = ptr->next->next;
				return;
			}
			else
			{
				ptr = ptr->next;
			}
		}
		else
		{
			return;
		}
	}
}

void memoryList::deleteEntry(_u32 id)
{
	memoryEntry* ptr = &start;

	for (;;)
	{
		if (ptr->next->next != nullptr)
		{
			if (ptr->next->id == id)
			{
				end.id = end.id + sizeof(memoryEntry) + ptr->next->size;
				ptr->next = ptr->next->next;

			}
			else
			{
				ptr = ptr->next;
			}
		}
		else
		{
			return;
		}
	}
}