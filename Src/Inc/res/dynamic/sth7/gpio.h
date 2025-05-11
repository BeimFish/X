#include"res/other/config.h"
#include"res/other/type.h"

struct IO_Type
{
  volatile _u32 MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  volatile _u32 OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  volatile _u32 OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  volatile _u32 PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  volatile _u32 IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  volatile _u32 ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  volatile _u32 BSRR;     /*!< GPIO port bit set/reset,               Address offset: 0x18      */
  volatile _u32 LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  volatile _u32 AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
};


enum ioPort
{
	A=0,B,C,D,E,F,G,H,I,J,K
};

class IO {
	IO_Type* ptr;

public:
	void init(_u8 ptr);
	void set(_u32 moder,_u16 otyper,_u8 pin = 16,_u32 pupdr = 0x55555555,_u32 ospeedr = 0);
};

