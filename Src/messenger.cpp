#include "messenger.h"

#if defined(USE_WINDOWS)||defined(USE_LINUX)
#include<mutex>
#else
#include"res/dynamic/sth7/mutex.h"
#endif


void Messenger::init()
{
#if defined(USE_WINDOWS)||defined(USE_LINUX)
	mutex = new std::mutex;
#else

#endif
	mutex->unlock();
}
void Messenger::send(_u32 email,_u8 target)
{

	mutex->lock();
	mailbox[target] = email;
	mutex->unlock();
	return;

}
_u32 Messenger::receive(_u8 target)
{

	return mailbox[target];

}
