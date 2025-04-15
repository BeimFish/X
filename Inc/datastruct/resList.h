#include"res/other/type.h"
enum resVector
{
	all=0,
	num,
	mutex
};

struct resEntry
{
	resEntry* next;

	void* address;  //��¼��Դ��ַ
	_u8 type;       //��¼��Դ����
	_u8 id;         //��ǰʹ�ø���Դ��task������Core��id
};

class resList
{
	resEntry start;
public:
	void init(_u16 id);
	void createEntry(resEntry& newEntry, _u8 id);
	void deleteEntry(_u8 id, _u8 type);
	void* readEntry(_u8 id, _u8 type);

};


