#include"type.h"
#include"config.h"
class bitMap;
class resList;
class resEntry;
class taskList;
class taskEntry;
class memoryList;

#if OS == 1
//Windows模式
namespace std {
    class mutex;    // 前向声明标准库的mutex类
    class thread;   // 前向声明标准库的thread类
}
#elif OS == 2 
//LINUX模式
#else
//未启用OS(系统)模式
#endif

#if NONE ==1
//CORTEX-M4模式
#elif OS == 2 
//CORTEX-M7模式
#else
//未启用NONE(裸机)模式
#endif


class core {
    _u8 cid;                                         //内核cid
    _u32 pid;                                        //当前执行的任务id
    _u32 execTaskNum;                                //记录执行任务的数量
    taskList* taskManager;                           //Task队列
    _u64 memoryManager[8];                           //私有内存池
#if OS == 1
    //Windows模式
    std::thread* thread;                        //core线程
#elif OS == 2 
    //LINUX模式
#else
    //未启用OS(系统)模式
#endif


public:                    

    void init(_u8 cid, void* ptr, _u32 size);                         //core初始化
    _u8 create(void(*ptr)(core*), void* res);                        //Task创建
    _u32 ACPT();                                                      //返回当前执行任务的tid
    _u32 taskLength();                                               //返回就绪任务的数量
    void* malloc(_u32 size, _u8 token = 0);                           //内存申请
    void free(void* ptr);                                            //内存释放
    void free(_u32 pid);                                            //内存释放
    void* getShare(_u8 token);                                      //获取共享内存地址
    void exec();

    /////////////////////////////////资源API///////////////////////////////////////
};
