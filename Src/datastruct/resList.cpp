#include <datastruct/resList.h>
void resList::init(_acptSize acpt)
{
	start.next = nullptr;
	start.address = nullptr;
	start.acpt = acpt;
	start.type = resVector::start;
}
void resList::createEntry(resEntry& newEntry,_u8 acpt)
{
	resEntry* ptr = &newEntry;
	for (_u16 i = 1;; i++)
	{

		if (ptr->next == nullptr)
		{
			ptr->acpt = acpt;
			ptr->next = start.next;
			start.next = &newEntry;
			start.type = start.type + i;
			return;
		}
		else
		{
			ptr->acpt = acpt;
			ptr = ptr->next;
		}
	}
}
void resList::deleteEntry(_acptSize acpt, _u8 type)
{
	resEntry* ptr = &start, * tem;
	_u8 i = 0, j = 0;
	for (i = 0; i < start.type; i++)
	{
		if ((ptr->next->acpt == acpt) && ((ptr->next->type == type) || (type == 0)))
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
					if ((ptr->next->acpt == acpt) && ((ptr->next->type == type) || (type == 0)))
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
void* resList::readEntry(_acptSize acpt, _u8 type)
{
	resEntry* ptr = &start;

	for (_u8 i = 0; i < start.type; i = i + 1)
	{
		if (ptr->next == nullptr)
		{
			return nullptr;
		}
		else if ((ptr->next->acpt == acpt) && (ptr->next->type == type))
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