ENTRY(Reset_Handler)
_Min_Stack_Size = 0x20000;
/*0x20000 = 128k*/ 
/*每个stack分配16k内存*/ 
_estack = end + 0x20000; 

MEMORY
{
  ITCMRAM  (xrw)     : ORIGIN = 0x00000000, LENGTH = 64K
  DTCMRAM  (xrw)     : ORIGIN = 0x20000000, LENGTH = 128K

  FLASH0    (rx)     : ORIGIN = 0x08000000, LENGTH = 2048K
  FLASH1    (rx)     : ORIGIN = 0x08100000, LENGTH = 1024K
  
  /*stack内存*/
  STACK    (xrw)     : ORIGIN = 0x24000000, LENGTH = 256K   
  /*heap内存*/
  HEAP     (xrw)     : ORIGIN = 0x30000000, LENGTH = 272K
  /*共享区*/
  SHARE    (xrw)     : ORIGIN = 0x38000000, LENGTH = 32K

}


SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) 
  } >FLASH1
  
  .text :
  {
    . = ALIGN(4);
    *(.text)         
    *(.text*)              
  } >FLASH1

  .stack :/*end为使用的栈区，end_x为不使用栈区，同时只能存在一个end*/
  {
    . = ALIGN(8);
    PROVIDE ( end_x = . );
    . = . + _Min_Stack_Size;
    
    . = ALIGN(8);
    PROVIDE ( end = . );
    . = . + _Min_Stack_Size;
  } >STACK
}
