/*
 * mutex.h
 *
 *  Created on: Mar 18, 2025
 *      Author: 29450
 */

#ifndef MUTEX_H
#define MUTEX_H
#include"res/other/type.h"
class MUTEX {

	alignas(4) volatile _u8 m = 0;  // 4 字节对齐的锁变量
public:
	void lock();
	void unlock();
};

#endif
