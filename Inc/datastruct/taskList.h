#include"res/other/type.h"
class Core;
class resList;



struct taskEntry
{
	taskEntry* next;
	void(*ptr)(Core*);    //��¼��������ַ
	resList* res;         //ӵ�е���Դ��
	_u32 id;         //��ǰʹ�ø���Դ��task������Core��id

};

class taskList
{
	taskEntry start;
public:
	void init(_u32 id);
	void createEntry(taskEntry& newEntry);
	void deleteEntry(_u32 id);
	taskEntry& move();
	taskEntry& exec(_u32& tid);

	_u32 listLength();

};


