#include"type.h"
#include"config.h"
class core;
class taskList;

class dispatcher
{
	_u8 id;				   // 对象id(dis的id是0，唯一的0号id，调度器)
	_u32 execIdNum;		   // 计数器,用于辅助生成内核id
	_u32 coreDispatchNum;  // 计数器,辅助内核调度
	taskList *taskManager; // 待调度分配Task队列
	_u64 memoryManager[8]; // 总内存池
	core *c;			   // 内核实例
public:
	void init();
	void create(void (*ptr)(core *), void *res);
	void exec();
};
