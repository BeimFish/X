

#include "manager.h"

void Manager::init()
{
	for(_u8 i=0;i<6;i++) m[i].unlock();

}
_u8 Manager::getGPIO(GPIO* &ptr)volatile
{
	ptr=new GPIO(16*5+5);
	return 0;
}
_u8 Manager::getMUTEX(MUTEX* &ptr)
{
	ptr = &m[0];
	return 0;
}
