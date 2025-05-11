#include "main.h"
#include<stdio.h>

#if defined(USE_WINDOWS) || defined(USE_LINUX)
#include<stdlib.h>
#else

#endif
#define pc *((int*)SHARESTART)
void fu()
{

	for (int i = 0; i < 5; i++)
	{


		pc =pc+i;
		//printf("%d\n",*a);
	}

}
void fun()
{

	for (int i = 0; i < 5; i++)
	{


		pc=i;
		//printf("%d\n",*a);
	}

}

// 将 posix 宏定义为指向函数指针的指针
#define sysCallTable(x) ((void (**)())((char*)SYSCALLTABLE + sizeof(void*)*x))

int main(void)
{
	pc = 0;
	*sysCallTable(0) = fu;      // 无需强制转换
	(*sysCallTable(0))();
	for (;;);
}
