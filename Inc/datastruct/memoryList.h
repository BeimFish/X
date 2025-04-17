#include"res/other/type.h"
#include"res/other/config.h"
struct memoryEntry
{
	memoryEntry* next;

	_ptrSize num;
	_u32 id;
	_ptrSize sptr;
	_ptrSize size;
};

class memoryList
{
	memoryEntry start, end;
public:
	void init(_u32 id);
	void* createEntry(_ptrSize size,_u32 id);
	void deleteEntry(void* ptr);
};