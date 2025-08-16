#include "resList.h"
void resList::init(_u16 id)
{
	start.next = nullptr;
	start.address = nullptr;
	start.id = id;
	start.type = 0;
}
void resList::createEntry(resEntry& newEntry,_u8 id)
{
	resEntry* ptr = &newEntry;
	for (_u16 i = 1;; i++)
	{

		if (ptr->next == nullptr)
		{
			ptr->id = id;
			ptr->next = start.next;
			start.next = &newEntry;
			start.type = start.type + i;
			return;
		}
		else
		{
			ptr->id = id;
			ptr = ptr->next;
		}
	}
}
void resList::deleteEntry(_u8 id, _u8 type)
{
	resEntry* ptr = &start, * tem;
	_u8 i = 0, j = 0;
	for (i = 0; i < start.type; i++)
	{
		if ((ptr->next->id == id) && ((ptr->next->type == type) || (type == 0)))
		{
			tem = ptr;
			for (j = 1;;)
			{
				if (ptr->next->next == nullptr)
				{
					tem->next = ptr->next->next;
					start.type -= j;
					break;
				}
				else
				{
					ptr = ptr->next;
					if ((ptr->next->id == id) && ((ptr->next->type == type) || (type == 0)))
					{
						j = j + 1;
					}
					else
					{
						tem->next = ptr->next;
						start.type -= j;
						break;
					}

				}
			}

		}
		ptr = ptr->next;
	}
	return;
}
void* resList::readEntry(_u8 id, _u8 type)
{
	resEntry* ptr = &start;

	for (_u8 i = 0; i < start.type; i = i + 1)
	{
		if (ptr->next == nullptr)
		{
			return nullptr;
		}
		else if ((ptr->next->id == id) && (ptr->next->type == type))
		{
			return ptr->next->address;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	return nullptr;
}