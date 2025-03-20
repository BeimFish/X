/*
 * messenge.cpp
 *
 *  Created on: Mar 16, 2025
 *      Author: 29450
 */

#include "messenger.h"
void Messenger::init()
{
	mutex.unlock();
}
void Messenger::send(_u32 email,_u8 target)
{

	mutex.lock();
	mailbox[target] = email;
	mutex.unlock();
	return;

}
_u32 Messenger::receive(_u8 target)
{

	return mailbox[target];

}
