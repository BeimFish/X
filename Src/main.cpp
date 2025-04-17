#include "main.h"
#include<stdio.h>



int pc = 0;

void fun(Core* core)
{
	for (int i = 0; i < 15; i++)
	{
		pc++;
		printf("ABCD\n");
	}
	//dispatcher.taskCreate(fun, 0);
}


void fu(Core* core)
{

	dispatcher.dispatchTask();
	//printf("%d\n", core->TID());
	
	taskEntry* t = new taskEntry;
	t->ptr = fu;
	t->next = nullptr;
	core->create(*t);


}


int main(void)
{
	int i = HEAPSIZE / (sizeof(_u64) + sizeof(memoryEntry));
	memoryList a;
	a.init(7);
	int y = 0, n = 0;




	_u64* as = (_u64*)a.createEntry(sizeof(as), 0);

	for (int k = 0; k < i - 1; k++)
	{
		if (a.createEntry(sizeof(as), 0) == nullptr)
		{
			n++;
		}
		else
		{
			y++;
		}
	}
	a.deleteEntry(as);



	for (;;);
}
