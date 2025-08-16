#include"type.h"


struct resEntry
{
	resEntry* next;

	void* address;  //资源指针
	_u8 type;       //资源类型
	_u8 id;         //当前使用该资源的任务id
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


