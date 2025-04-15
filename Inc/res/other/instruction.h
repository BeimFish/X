#include "res\other\config.h"


#ifdef USE_ARM//内存屏障
#define DMB asm volatile("dmb sy":::"memory")
#define ISB asm volatile("isb sy":::"memory")
#define DSB asm volatile("dsb sy":::"memory")
#else
#define DMB
#define ISB
#define DSB
#endif
