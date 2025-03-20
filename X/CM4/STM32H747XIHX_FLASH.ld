
ENTRY(Reset_Handler)

_estack = ORIGIN(RAM1) + LENGTH(RAM1);    
_Min_Heap_Size = 0x200;     
_Min_Stack_Size = 0x400; 

MEMORY
{
  FLASH    (rx)     : ORIGIN = 0x08100000, LENGTH = 1024K

  AXI_SRAM (xrw)    : ORIGIN = 0x24040000, LENGTH = 256K 
  RAM1     (xrw)    : ORIGIN = 0x30000000, LENGTH = 128K
  
  /*共享区*/
  RAM4     (xrw)    : ORIGIN = 0x38000000, LENGTH = 32K

  /*其他内核空间*/
  RAM2     (xrw)     : ORIGIN = 0x30020000, LENGTH = 128K
  RAM3     (xrw)    : ORIGIN = 0x30040000, LENGTH = 16K

}


SECTIONS
{
 
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) 
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)          
    *(.text*)         
    . = ALIGN(4);
    _etext = .;       
  } >FLASH

  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */


    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >AXI_SRAM AT> FLASH

  . = ALIGN(4);
  .bss :
  {
    _sbss = .;        
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)

    . = ALIGN(4);
    _ebss = .;       
    __bss_end__ = _ebss;
  } >AXI_SRAM

 
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM1
}


