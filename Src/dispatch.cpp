#include "dispatch.h"
#include"Core.h"
#include"datastruct/taskList.h"
void Dispatcher::init()
{
    id = 0;
    reg = 0;
    start = new coreEntry;
    start->next = nullptr;
    start->core = 0;

    task = new taskList;
    task->init(id);

}
void Dispatcher::coreCreate(Core& c)
{
    c.init(5 + (_u32)start->core);
    start->core = (Core*)((_u8)start->core + 1);
    coreEntry* tem = new coreEntry;
    tem->next = start->next;
    tem->core = &c;
    start->next = tem;
}
void Dispatcher::taskCreate(void(*ptr)(Core*),void* res)
{
    taskEntry* tem = new taskEntry;
    tem->next = nullptr;
    tem->ptr = ptr;
    tem->res = (resList*)res;
    task->createEntry(*tem);
    

}
void Dispatcher::dispatchTask()
{//重新考虑，应为死循环
    coreEntry* ptr;
   
    for (_u16 i =0;i<20;i++)
    {
        reg = 0;
        ptr = start;

        if ((start->next == nullptr) || (task->listLength() == 0))
        {
            continue;
        }

        for (; ptr->next != nullptr;)
        {
            ptr = ptr->next;
            reg += ptr->core->taskLength();
        }
        reg = reg / (_u32)start->core;
        ptr = start->next;
        for (;;)
        {
            if (ptr->core->taskLength() <= reg)
            {
                ptr->core->create(task->move());
                break;
            }
            else if (ptr->next != nullptr)
            {
                
                ptr = ptr->next;
            }
            else
            {
                break;
            }
        }

    }
    return;
}