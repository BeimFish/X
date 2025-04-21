#include "main.h"
#include<stdio.h>

#if defined(USE_WINDOWS)
#include<stdlib.h>
#else 

#endif

int pc = 0;

void fun(Core* core)
{
	_u64* a = (_u64*)core->malloc(sizeof(_u64) * 100);
	  
	for (int i = 0; i < 100; i++)
	{
		a[i] = i;
		printf("%2d:%5d:  %#x\n",a[i], pc++,core->ACPT());
	}

}



int main(void)
{

	manager.init();
	Core c,d;

	c.init(5, manager.creatMemory(64 * 1024), 64 * 1024);
	d.init(6, manager.creatMemory(64 * 1024), 64 * 1024);


	for (int i = 0; i < 100; i++)
	{
		d.create(fun, 0);
		c.create(fun,0);
	}
	
	

	c.exec();
	d.exec();

	for (;;);
}
