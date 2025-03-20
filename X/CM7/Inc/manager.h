

#ifndef MANAGER_H
#define MANAGER_H

#include"res/dynamic/sth7/gpio.h"
#include"res/dynamic/sth7/mutex.h"

class Manager {
	MUTEX m[6];
public:
	void init();
	_u8 getGPIO(GPIO* &ptr)volatile;
	_u8 getMUTEX(MUTEX* &ptr);
};

#endif /* MANAGER_H_ */
