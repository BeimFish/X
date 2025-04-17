#include"datastruct/memoryList.h"

#if defined(USE_WINDOWS) || defined(USE_LINUX)
#include<stdlib.h>
#else

#endif

void memoryList::init(_u32 id)
{
	start.num = (_ptrSize)malloc(HEAPSIZE);    //堆内存起始地址

	start.next = &end;
	start.id = id;

	start.size = 0;                       
	start.sptr = start.num;


	end.next = nullptr;
	end.id = id;

	end.size = 0;                                                     //当前已使用堆内存
	end.sptr = start.num + HEAPSIZE + sizeof(memoryEntry);            //堆内存结束地址+sizeof(memoryEntry)




	end.num = HEAPSIZE;//剩余可用空间
}
void* memoryList::createEntry(_ptrSize size,_u32 id)
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
			end.num = end.num - sizeof(memoryEntry) - size;
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
				end.num = end.num + sizeof(memoryEntry) + ptr->next->size;
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















	if (((_ptrSize)dptr > start.sptr) && ((_ptrSize)dptr > end.sptr - sizeof(memoryEntry)))
	{
		memoryEntry* ptr = start.next;


		for (;;)
		{
			if ((_ptrSize)dptr == ptr->sptr)
			{
				
			}
		}
	}

	return;
}