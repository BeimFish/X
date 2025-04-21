#include <datastruct/bitMap.h>
void bitMap::init(_acptSize acpt)
{
	this->acpt = acpt;
	map = 0;
}
void bitMap::upDate(_u8 date, _u8 bit)
{
	map &= ~(0x01 << bit);
	map |= (date << bit);

}
_u8 bitMap::empty(_u32 bitMask)
{
	if ((map & bitMask) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
_u8 bitMap::readEmpty()
{
	decltype(map) mark = ~0ULL;             //��ʼ����
	_u8 i = 0, j = sizeof(map) * 8;         //i:��ǰλ��j:��ǰ�����С
	while (1)
	{
		if ((map & mark) == 0)              //ȫ0��
		{
			return i;
		}
		else if ((map & mark) == mark)      //ȫ1��
		{
			if (j == sizeof(map) * 8) return 0xff;
			else { i += j; }
		}
		else                               //01��Ͽ�
		{
			j = j / 2;
		}
		mark = ((0x01ULL << j) - 1) << i;  //�������
	}
}




