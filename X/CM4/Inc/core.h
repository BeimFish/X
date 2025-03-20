

#include"res/dynamic/sth7/gpio.h"
#include"res/dynamic/sth7/mutex.h"
struct ID;

class Core
{
	_u32 Arcthitecturn;
	_u32 Partno;
	ID* id;
	//NVIC
	//Control
	//FPE
	//MPU
	//SysTick
public:
	void (*taskPtr)(Core& Core);
	GPIO* gpio;
	MUTEX* mutex;
	Core& init();

	//DBG
	//RCC
	//GPIO
	//...
};


