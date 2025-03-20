#include "main.h"


int main(void)
{

	Core d;
	d.init();
	messenger->init();
	manager->init();

	for(int i = 0;;i++)
	{

		//manager->getMUTEX(d.mutex);
		messenger->send( i, 3);
	}


}
