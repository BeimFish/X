/*
 * gpio.cpp
 *
 *  Created on: Mar 16, 2025
 *      Author: 29450
 */

#include "res/dynamic/sth7/gpio.h"
#include"res/other/address/arm_address.h"

void IO::init(_u8 port)
{
	this->ptr=(IO_Type*)CM_AHB1_BASE+0x0400*port;
}

void IO::set(_u32 moder,_u16 otyper,_u8 pin,_u32 pupdr,_u32 ospeedr)
{
	if(pin != 16)
	{
		ptr->MODER &= ~(0x11<<pin*2);
		ptr->MODER |= (moder<<pin*2);

		ptr->OTYPER &= ~(0x01<<pin);
		ptr->OTYPER |= (otyper<<pin);

		ptr->PUPDR &= ~(0x11<<pin*2);
		ptr->PUPDR |= (pupdr<<pin*2);

		ptr->OSPEEDR &= ~(0x11<<pin*2);
		ptr->OSPEEDR |= (ospeedr<<pin*2);
	}
	else
	{
		ptr->MODER = moder;
		ptr->OTYPER = otyper;
		ptr->PUPDR = pupdr;
		ptr->OSPEEDR = ospeedr;
	}
}





/*
GPIO::~GPIO()
{
	delete ptr;
}
 GPIO& GPIO::config(_u8 bit,_u64 pinConfig,_u64 deviceConfig)
{
	if(bit<16)
	{
		ptr->MODER &= ~(0x3<<(bit*2));
		ptr->MODER |= ((pinConfig&0x03)<<(bit*2));

		ptr->OTYPER &= ~((0x4>>2)<<(bit*2));
		ptr->OTYPER |= (((pinConfig&0x04)>>2)<<(bit*2));

		ptr->PUPDR &= ~(0x11<<(bit*2));
		ptr->PUPDR |= (((deviceConfig&0x0C)>>2)<<(bit*2));

		ptr->OSPEEDR &= ~(0x11<<(bit*2));
		ptr->OSPEEDR |= ((deviceConfig&0x03)<<(bit*2));


	}
	else
	{
		ptr->OTYPER = (pinConfig & 0xffffffff);
		ptr->MODER = (pinConfig & (0xffff<<32));
		ptr->OSPEEDR = (deviceConfig & 0xffffffff);
		ptr->PUPDR = (deviceConfig & (0xffffffff<<32));
	}
	return *this;
}
 GPIO& GPIO::opuPut(_u8 bit,_u16 signal)
{
	if(bit<16)
	{

		ptr->ODR &= ~(0x01<<bit);
		ptr->ODR |= (signal<<bit);
	}
	else
	{
		ptr->ODR = signal;
	}
	return *this;
}
_u16 GPIO::inPut(_u8 bit)
{
	if(bit>16) return ptr->IDR;
	else return (ptr->IDR>>bit)&0x01;
}
*/
