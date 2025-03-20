#include"core.h"
#include"manager.h"
#include"messenger.h"

#define messenger ((Messenger*)(0x38000000))
#define manager ((Manager*)((_u8*)messenger + sizeof(Messenger)))


