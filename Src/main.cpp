#include "main.h"
#include<stdio.h>

#if defined(USE_WINDOWS) || defined(USE_LINUX)
#include<stdlib.h>
#else

#endif

int pc = 0;

void fun(Core* core)
{
	_u64* a = (_u64*)core->malloc(sizeof(_u64));

	for (int i = 0; i < 20; i++)
	{
		*a = i;
		//printf("%d\n",*a);
	}

}



int main(void)
{

	manager.init();
	Core c;
	//c.init(5, manager.creatMemory(16 * 1024, 5), 16 * 1024);
	c.init(5, manager.creatMemory(1024, 5), 1024);

	c.create(fun, 0);


	c.exec();
	for (;;);
}
