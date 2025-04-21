#include"res/other/type.h"
#include"res/other/config.h"
class bitMap;
class resList;
class resEntry;
class taskList;
class taskEntry;
class memoryList;

#if defined(USE_WINDOWS)
namespace std {
    class mutex;    // 前向声明标准库的mutex类
    class thread;   // 前向声明标准库的thread类
}
#else
class MUTEX;        // 自定义的MUTEX类前向声明（非标准）
#endif


class Core {
    _u8 cid;                                         //内核cid
    _u32 acpt;                                        //当前执行的任务id
    _u32 execTaskNum;                                //记录执行任务的数量
    resList* resManager;                             //资源管理
    taskList* taskManager;                           //Task队列
    _u64 memoryManager[8];                           //私有内存池
#if defined(USE_WINDOWS)
    std::thread* thread;                        //Core线程
#endif
    void free(_u32 acpt);

public:                    

    void init(_u8 cid, void* ptr, _u32 size);                         //Core初始化
    _u8 create(void(*ptr)(Core*), void* res);                        //Task创建
    _u32 ACPT();                                                      //返回当前执行任务的tid
    _u32 taskLength();                                               //返回就绪任务的数量
    void* malloc(_u32 size);                                         //内存申请
    void free(void* ptr);                                            //内存释放
    void exec();

    /////////////////////////////////资源API///////////////////////////////////////
#if defined(USE_WINDOWS)
    std::mutex* mutex(_u8 taskId);
#else
    MUTEX* mutex(_u8 taskId);
#endif
};
