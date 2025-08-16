_Min_Stack_Size = 0x1000;
/*0x1000 = 4k*/ 
_estack = end + 0x1000; 



MEMORY
{
  STACK    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 4K
  POSIX    (xrw)    : ORIGIN = 0x20001000,   LENGTH = 1K
  HEAP     (xrw)    : ORIGIN = 0x20001400,   LENGTH = 4K
  SHARE    (xrw)    : ORIGIN = 0x20002400,   LENGTH = 1K
  
  FLASH    (rx)     : ORIGIN = 0x8000000,   LENGTH = 32K
}



SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) 
  } >FLASH
  
  .text :
  {
    . = ALIGN(4);
    *(.text)         
    *(.text*)              
  } >FLASH



  .stack :/*end为使用的栈区，end_x为不使用栈区，同时只能存在一个end*/
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    . = . + _Min_Stack_Size;
  } >STACK
  
  .posix :
  {
    . = ALIGN(4);
          
  } >POSIX
}
