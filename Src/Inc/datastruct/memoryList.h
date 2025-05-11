#include"res/other/type.h"
#include"res/other/config.h"
struct memoryEntry
{
	memoryEntry* next;

	_u32 id;        //指向申请该内存的任务
	_ptrSize sptr;  //指向内存块数据段地址
	_ptrSize size;  //内存块数据段大小
};

class memoryList
{
	memoryEntry start, end;
public:
	void init(void* sptr, _u32 size, _u32 id);
	void* createEntry(_u32 size,_u32 id);
	void deleteEntry(void* ptr);
	void deleteEntry(_u32 id);
};