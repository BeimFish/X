#include"res/other/type.h"
class MUTEX {

	volatile _u8 m = 0;  // 4 字节对齐的锁变量
public:
	void lock();
	void unlock();
};


