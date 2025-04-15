

#include"res/other/type.h"
#include"res/other/instruction.h"

#if defined(USE_WINDOWS)||defined(USE_LINUX)
namespace std {
	class mutex;
}
#else
class MUTEX;
#endif
class Core;

class Messenger
{
	_u32 mailbox[16];
public:
#if defined(USE_WINDOWS)||defined(USE_LINUX)
	std::mutex* mutex;
#else
	MUTEX* mutex;
#endif
	void init();
	void send(_u32 email,_u8 target);
	_u32 receive(_u8 target);
};


