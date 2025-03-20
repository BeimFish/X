
#include "res/dynamic/sth7/MUTEX.h"

void MUTEX::lock()
{

         asm volatile (
        	 "lock_loop:         \n\t"
             "ldrex r0, [%0]     \n\t"  // 独占加载
             "cmp   r0, #1       \n\t"
             "beq   lock_loop    \n\t"
             "mov   r0, #1       \n\t"
             "strex r1, r0, [%0] \n\t"
        	 "cmp   r1, #0       \n\t"
        	 "bne   lock_loop    \n\t"
             :
             : "r" (&m)
             : "r0","memory"
         );
     asm volatile("dsb sy":::);
}
void MUTEX::unlock()
{
	m=0;

}
