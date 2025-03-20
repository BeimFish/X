#include "res\other\config.h"

#if defined(USE_CM0)||defined(USE_CM3)||defined(USE_CM4)||defined(USE_CM7)
#define USE_CM
#endif

#ifdef USE_ARM//内存屏障
#define DMB asm volatile("dmb sy":::"memory")
#define ISB asm volatile("isb sy":::"memory")
#define DSB asm volatile("dsb sy":::"memory")
#else
#define DMB
#define ISB
#define DSB
#endif
