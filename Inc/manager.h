#include"res/other/type.h"
#include"res/other/config.h"
class memoryList;

class Manager {
	_u32 id;
	_u64 memory[8];
public:
	void init();
	void* creatMemory(_u32 size,_u32 id);
	void deleteMemory(void* sptr);



};

