#include"type.h"
#include"config.h"
struct memoryEntry
{
	memoryEntry* next;//指向相邻的后一个内存块

	_u8 token;     //用于标记共享内存的类型，（0：非共享内存类型）
	_u32 id;        //指向申请该内存的任务
	_ptrSize sptr;  //指向内存块数据段地址
	_ptrSize size;  //内存块数据段大小
};

class memoryList
{
	memoryEntry start, end;
public:
	void init(void* sptr, _u32 size, _u32 id);
	void* createEntry(_u32 size, _u32 id, _u8 token = 0);
	void* getShare(_u32 token);
	void deleteEntry(void* ptr);
	void deleteEntry(_u32 id);
};