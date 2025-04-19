#define CACHE
/*
 * CACHER：存在缓存
 * NOCACHER：不存在缓存
 */
#define USE_ARM
/*
 * USE_ARM：使用ARM架构
 * USE_X86
 */
#define USE_CM7
/*
 * USE_CM4：使用CM4内核
 * USE_CM7：使用CM7内核
 * USE_WINDOWS：使用Windows系统
 * USE_LINUX：使用Linux系统
 */

#define HEAPSIZE 256*1024
 /*
 * 系统可用堆内存大小
 * 以B为单位
 * WINDOWS下不要申请太大，需要考虑内存中是否存在足够大的连续内存块
 */
#define HEAPSTART (void*)0x24000000
 /*
 * 栈区的起始地址
 * 该地址为void*类型
 */










