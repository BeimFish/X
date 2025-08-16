#include"type.h"


struct bitMap
{
	void init();
	void upDate(_u8 date, _u8 bit);
	_u8 empty(_u32 bitMask = 0xffffffff);
	_u8 readEmpty();
private:
	_u32 map;

};






