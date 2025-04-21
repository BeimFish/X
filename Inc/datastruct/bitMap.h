#include"res/other/type.h"

struct bitMap
{
	void init(_acptSize acpt);
	void upDate(_u8 date, _u8 bit);
	_u8 empty(_u32 bitMask = 0xffffffff);
	_u8 readEmpty();
private:
	_u32 map;
	_acptSize acpt;

};






