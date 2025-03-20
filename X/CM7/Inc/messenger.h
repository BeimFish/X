/*
 * messenge.h
 *
 *  Created on: Mar 16, 2025
 *      Author: 29450
 */

#ifndef MESSENGE_H
#define MESSENGE_H
#include"res/other/type.h"
#include"res/other/instruction.h"
#include"res/dynamic/sth7/mutex.h"
class Core;
class Messenger
{
	MUTEX mutex;
	_u32 mailbox[16];
public:
	void init();
	void send(_u32 email,_u8 target);
	_u32 receive(_u8 target);
};

#endif /* MESSENGE_H_ */
