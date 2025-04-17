#include"res/other/type.h"
#include"res/other/config.h"
class Core;
class taskList;
class taskEntry;

struct coreEntry
{
    Core* core;
    coreEntry* next;
};

class Dispatcher 
{
    _u8 id;
    _u32 reg;
    coreEntry* start;
    taskList* task;
 
public:
    void init();
    void coreCreate(Core& c);
    void taskCreate(void(*ptr)(Core*), void* res);
    void dispatchTask();

};
