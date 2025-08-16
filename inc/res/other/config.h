#define CACHE
/*
 * CACHER：存在缓存
 * NOCACHER：不存在缓存
 */


#define OS 0
 /*
 * 0: 不启用系统模式
 * 1：使用Windows系统
 * 2：使用Linux系统
  */

#define NONE 1
 /*
 *  0：不启用裸机模式
  * 1：使用CM4内核
  * 2：使用CM7内核
  */

#define HEAPSIZE 1*1024
 /*
 * 系统可用堆内存大小
 * 以B为单位
 * WINDOWS下不要申请太大，需要考虑内存中是否存在足够大的连续内存块
 */

#define CORENUM 2
 /*
 * 内核数量
 */

#define COREMEMORYSIZE 256
/*
 * 每个内核分配到的堆内存大小
 * 不要全部占用HEAPSIZE! 留下部分予调度器使用
 */




#define HEAPSTART 0
 /*
 * 栈区的起始地址
 * 仅在WINDOWS或LINUX模式下使用，其他情况下均为0
 */

#define SHARESTART 0
 /*
 * 共享区的起始地址
 * 仅在WINDOWS或LINUX模式下使用，其他情况下均为0
 */

#define SYSCALLTABLE 0
 /*
 * 系统调用表的起始区域
 * 仅在WINDOWS或LINUX模式下使用，其他情况下均为0
 */












