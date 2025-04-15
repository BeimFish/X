#include"res/other/type.h"
#include"res/other/config.h"
class bitMap;
class resList;
class resEntry;
class taskList;
class taskEntry;


#if defined(USE_WINDOWS) || defined(USE_LINUX)
namespace std {
    class mutex;    // 前向声明标准库的mutex类
    class thread;   // 前向声明标准库的thread类
}
#else
class MUTEX;        // 自定义的MUTEX类前向声明（非标准）
#endif


class Core {
    _u16 id;                                     //内核id
    _u32 tid;                                   //当前执行的任务id
    _u32 execTaskNum;                           //记录执行任务的数量
    resList* resMessenger;                      //资源管理
    taskList* taskMessenger;                    //Task队列
#if defined(USE_WINDOWS) || defined(USE_LINUX)
    std::thread* thread;                        //Core线程
#endif



public:                    //释放资源

    void init(_u8 id);                                               //Core初始化
    _u8 create(taskEntry& newTask);                   //Task创建
    _u32 TID();
    _u32 taskLength();

    /////////////////////////////////资源API///////////////////////////////////////
#if defined(USE_WINDOWS)
    std::mutex* mutex(_u8 taskId);
#else
    MUTEX* mutex(_u8 taskId);
#endif
};
