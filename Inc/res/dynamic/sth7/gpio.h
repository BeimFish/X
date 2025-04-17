
#include"res/other/type.h"
struct GPIO_Type
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
class GPIO {
	GPIO_Type* ptr;
public:
	GPIO(_u8 Pin);
	/*
	 * Pin：0~15GPIOA,16~31,GPIOB...
	 */
	GPIO& config(_u8 bit,_u64 pinConfig,_u64 deviceConfig);
	/*
	 * bit：大于16为块操作，小于16为位操作
	 *
	 * pinConfig = OTYPE + MODER  [MODER,OTYPE]
	 * MODER：00输入，01输出，10复用，11模拟
	 * OTYPER：0推挽，1开漏
	 *
	 * deviceConfig = OSPEEDR + PUPDR  [PUPDE,OSPEED]
	 * OSPEER：00，01，10，11
	 * PUPDR：01上拉，10下拉，00浮空
	 */
	GPIO& opuPut(_u8 bit,_u16 signal);
	/*
	 * bit：大于16为块操作，小于16为位操
	 *
	 * signal：输出状态
	 */
	_u16 inPut(_u8 bit);
	/*
	 * bit：大于16为块操作，小于16为位操
	 */
	~GPIO();

};

