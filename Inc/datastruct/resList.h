#include"res/other/type.h"
enum resVector
{
	start = 0,
	mutex,
	end
};

struct resEntry
{
	resEntry* next;

	void* address;  //资源指针
	_u8 type;       //资源类型
	_acptSize acpt;         //当前使用该资源的任务id
};

class resList
{
	resEntry start;
public:
	void init(_acptSize acpt);
	void createEntry(resEntry& newEntry, _u8 acpt);
	void deleteEntry(_acptSize acpt, _u8 type);
	void* readEntry(_acptSize acpt, _u8 type);

};


