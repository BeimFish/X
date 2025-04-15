#include "main.h"
#include<stdio.h>
void fun(Core* core)
{
	printf("a456ddsd");
}

int main(void)
{

	Core d;
	taskEntry s;
	s.id = 7;
	s.next =nullptr;
	s.ptr = fun;

	d.init(5);
	d.create(s);
	for (;;);
}
