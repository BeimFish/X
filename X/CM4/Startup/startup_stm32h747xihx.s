

.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.global g_pfnVectors
.global Default_Handler


.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss


  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit

/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the application's entry point.*/
  bl main

LoopForever:
  b LoopForever

  .size Reset_Handler, .-Reset_Handler


  .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler

/******************************************************************************
*
* The STM32H747XIHx vector table.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object

g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word	MemManage_Handler
  .word	BusFault_Handler
  .word	UsageFault_Handler
  .word	0
  .word	0
  .word	0
  .word	0
  .word	SVC_Handler
  .word	DebugMon_Handler
  .word	0
  .word	PendSV_Handler
  .word	SysTick_Handler
  .word	WWDG2_IRQHandler                 			/* Window Watchdog interrupt                   */
  .word	PVD_PVM_IRQHandler               			/* PVD through EXTI line                       */
  .word	RTC_TAMP_STAMP_CSS_LSE_IRQHandler			/* RTC tamper, timestamp                       */
  .word	RTC_WKUP_IRQHandler              			/* RTC Wakeup interrupt                        */
  .word	FLASH_IRQHandler                 			/* Flash memory                                */
  .word	RCC_IRQHandler                   			/* RCC global interrupt                        */
  .word	EXTI0_IRQHandler                 			/* EXTI Line 0 interrupt                       */
  .word	EXTI1_IRQHandler                 			/* EXTI Line 1 interrupt                       */
  .word	EXTI2_IRQHandler                 			/* EXTI Line 2 interrupt                       */
  .word	EXTI3_IRQHandler                 			/* EXTI Line 3interrupt                        */
  .word	EXTI4_IRQHandler                 			/* EXTI Line 4interrupt                        */
  .word	DMA_STR0_IRQHandler              			/* DMA1 Stream0                                */
  .word	DMA_STR1_IRQHandler              			/* DMA1 Stream1                                */
  .word	DMA_STR2_IRQHandler              			/* DMA1 Stream2                                */
  .word	DMA_STR3_IRQHandler              			/* DMA1 Stream3                                */
  .word	DMA_STR4_IRQHandler              			/* DMA1 Stream4                                */
  .word	DMA_STR5_IRQHandler              			/* DMA1 Stream5                                */
  .word	DMA_STR6_IRQHandler              			/* DMA1 Stream6                                */
  .word	ADC1_2_IRQHandler                			/* ADC1 and ADC2                               */
  .word	FDCAN1_IT0_IRQHandler            			/* FDCAN1 Interrupt 0                          */
  .word	FDCAN2_IT0_IRQHandler            			/* FDCAN2 Interrupt 0                          */
  .word	FDCAN1_IT1_IRQHandler            			/* FDCAN1 Interrupt 1                          */
  .word	FDCAN2_IT1_IRQHandler            			/* FDCAN2 Interrupt 1                          */
  .word	EXTI9_5_IRQHandler               			/* EXTI Line[9:5] interrupts                   */
  .word	TIM1_BRK_IRQHandler              			/* TIM1 break interrupt                        */
  .word	TIM1_UP_IRQHandler               			/* TIM1 update interrupt                       */
  .word	TIM1_TRG_COM_IRQHandler          			/* TIM1 trigger and commutation                */
  .word	TIM_CC_IRQHandler                			/* TIM1 capture / compare                      */
  .word	TIM2_IRQHandler                  			/* TIM2 global interrupt                       */
  .word	TIM3_IRQHandler                  			/* TIM3 global interrupt                       */
  .word	TIM4_IRQHandler                  			/* TIM4 global interrupt                       */
  .word	I2C1_EV_IRQHandler               			/* I2C1 event interrupt                        */
  .word	I2C1_ER_IRQHandler               			/* I2C1 error interrupt                        */
  .word	I2C2_EV_IRQHandler               			/* I2C2 event interrupt                        */
  .word	I2C2_ER_IRQHandler               			/* I2C2 error interrupt                        */
  .word	SPI1_IRQHandler                  			/* SPI1 global interrupt                       */
  .word	SPI2_IRQHandler                  			/* SPI2 global interrupt                       */
  .word	USART1_IRQHandler                			/* USART1 global interrupt                     */
  .word	USART2_IRQHandler                			/* USART2 global interrupt                     */
  .word	USART3_IRQHandler                			/* USART3 global interrupt                     */
  .word	EXTI15_10_IRQHandler             			/* EXTI Line[15:10] interrupts                 */
  .word	RTC_ALARM_IRQHandler             			/* RTC alarms (A and B)                        */
  .word	0                                			/* Reserved                                    */
  .word	TIM8_BRK_TIM12_IRQHandler        			/* TIM8 and 12 break global                    */
  .word	TIM8_UP_TIM13_IRQHandler         			/* TIM8 and 13 update global                   */
  .word	TIM8_TRG_COM_TIM14_IRQHandler    			/* TIM8 and 14 trigger /commutation and global */
  .word	TIM8_CC_IRQHandler               			/* TIM8 capture / compare                      */
  .word	DMA1_STR7_IRQHandler             			/* DMA1 Stream7                                */
  .word	FMC_IRQHandler                   			/* FMC global interrupt                        */
  .word	SDMMC1_IRQHandler                			/* SDMMC global interrupt                      */
  .word	TIM5_IRQHandler                  			/* TIM5 global interrupt                       */
  .word	SPI3_IRQHandler                  			/* SPI3 global interrupt                       */
  .word	UART4_IRQHandler                 			/* UART4 global interrupt                      */
  .word	UART5_IRQHandler                 			/* UART5 global interrupt                      */
  .word	TIM6_DAC_IRQHandler              			/* TIM6 global interrupt                       */
  .word	TIM7_IRQHandler                  			/* TIM7 global interrupt                       */
  .word	DMA2_STR0_IRQHandler             			/* DMA2 Stream0 interrupt                      */
  .word	DMA2_STR1_IRQHandler             			/* DMA2 Stream1 interrupt                      */
  .word	DMA2_STR2_IRQHandler             			/* DMA2 Stream2 interrupt                      */
  .word	DMA2_STR3_IRQHandler             			/* DMA2 Stream3 interrupt                      */
  .word	DMA2_STR4_IRQHandler             			/* DMA2 Stream4 interrupt                      */
  .word	ETH_IRQHandler                   			/* Ethernet global interrupt                   */
  .word	ETH_WKUP_IRQHandler              			/* Ethernet wakeup through EXTI                */
  .word	FDCAN_CAL_IRQHandler             			/* CAN2TX interrupts                           */
  .word	cm7_sev_it_IRQHandler            			/* ArmÃ‚Â® CortexÃ‚Â®-M7 Send                  */
  .word	0                                			/* Reserved                                    */
  .word	0                                			/* Reserved                                    */
  .word	0                                			/* Reserved                                    */
  .word	DMA2_STR5_IRQHandler             			/* DMA2 Stream5 interrupt                      */
  .word	DMA2_STR6_IRQHandler             			/* DMA2 Stream6 interrupt                      */
  .word	DMA2_STR7_IRQHandler             			/* DMA2 Stream7 interrupt                      */
  .word	USART6_IRQHandler                			/* USART6 global interrupt                     */
  .word	I2C3_EV_IRQHandler               			/* I2C3 event interrupt                        */
  .word	I2C3_ER_IRQHandler               			/* I2C3 error interrupt                        */
  .word	OTG_HS_EP1_OUT_IRQHandler        			/* OTG_HS out global interrupt                 */
  .word	OTG_HS_EP1_IN_IRQHandler         			/* OTG_HS in global interrupt                  */
  .word	OTG_HS_WKUP_IRQHandler           			/* OTG_HS wakeup interrupt                     */
  .word	OTG_HS_IRQHandler                			/* OTG_HS global interrupt                     */
  .word	DCMI_IRQHandler                  			/* DCMI global interrupt                       */
  .word	0                                			/* Reserved                                    */
  .word	HASH_RNG_IRQHandler              			/* HASH and RNG global interrupt               */
  .word	FPU_IRQHandler                   			/* CPU2                                        */
  .word	UART7_IRQHandler                 			/* UART7 global interrupt                      */
  .word	UART8_IRQHandler                 			/* UART8 global interrupt                      */
  .word	SPI4_IRQHandler                  			/* SPI4 global interrupt                       */
  .word	SPI5_IRQHandler                  			/* SPI5 global interrupt                       */
  .word	SPI6_IRQHandler                  			/* SPI6 global interrupt                       */
  .word	SAI1_IRQHandler                  			/* SAI1 global interrupt                       */
  .word	LTDC_IRQHandler                  			/* LCD-TFT global interrupt                    */
  .word	LTDC_ER_IRQHandler               			/* LCD-TFT error interrupt                     */
  .word	DMA2D_IRQHandler                 			/* DMA2D global interrupt                      */
  .word	SAI2_IRQHandler                  			/* SAI2 global interrupt                       */
  .word	QUADSPI_IRQHandler               			/* QuadSPI global interrupt                    */
  .word	LPTIM1_IRQHandler                			/* LPTIM1 global interrupt                     */
  .word	CEC_IRQHandler                   			/* HDMI-CEC global interrupt                   */
  .word	I2C4_EV_IRQHandler               			/* I2C4 event interrupt                        */
  .word	I2C4_ER_IRQHandler               			/* I2C4 error interrupt                        */
  .word	SPDIF_IRQHandler                 			/* SPDIFRX global interrupt                    */
  .word	OTG_FS_EP1_OUT_IRQHandler        			/* OTG_FS out global interrupt                 */
  .word	OTG_FS_EP1_IN_IRQHandler         			/* OTG_FS in global interrupt                  */
  .word	OTG_FS_WKUP_IRQHandler           			/* OTG_FS wakeup                               */
  .word	OTG_FS_IRQHandler                			/* OTG_FS global interrupt                     */
  .word	DMAMUX1_OV_IRQHandler            			/* DMAMUX1 overrun interrupt                   */
  .word	HRTIM1_MST_IRQHandler            			/* HRTIM1 master timer interrupt               */
  .word	HRTIM1_TIMA_IRQHandler           			/* HRTIM1 timer A interrupt                    */
  .word	HRTIM_TIMB_IRQHandler            			/* HRTIM1 timer B interrupt                    */
  .word	HRTIM1_TIMC_IRQHandler           			/* HRTIM1 timer C interrupt                    */
  .word	HRTIM1_TIMD_IRQHandler           			/* HRTIM1 timer D interrupt                    */
  .word	HRTIM_TIME_IRQHandler            			/* HRTIM1 timer E interrupt                    */
  .word	HRTIM1_FLT_IRQHandler            			/* HRTIM1 fault interrupt                      */
  .word	DFSDM1_FLT0_IRQHandler           			/* DFSDM1 filter 0 interrupt                   */
  .word	DFSDM1_FLT1_IRQHandler           			/* DFSDM1 filter 1 interrupt                   */
  .word	DFSDM1_FLT2_IRQHandler           			/* DFSDM1 filter 2 interrupt                   */
  .word	DFSDM1_FLT3_IRQHandler           			/* DFSDM1 filter 3 interrupt                   */
  .word	SAI3_IRQHandler                  			/* SAI3 global interrupt                       */
  .word	SWPMI1_IRQHandler                			/* SWPMI global interrupt                      */
  .word	TIM15_IRQHandler                 			/* TIM15 global interrupt                      */
  .word	TIM16_IRQHandler                 			/* TIM16 global interrupt                      */
  .word	TIM17_IRQHandler                 			/* TIM17 global interrupt                      */
  .word	MDIOS_WKUP_IRQHandler            			/* MDIOS wakeup                                */
  .word	MDIOS_IRQHandler                 			/* MDIOS global interrupt                      */
  .word	JPEG_IRQHandler                  			/* JPEG global interrupt                       */
  .word	MDMA_IRQHandler                  			/* MDMA                                        */
  .word	0                                			/* Reserved                                    */
  .word	SDMMC_IRQHandler                 			/* SDMMC global interrupt                      */
  .word	0                                			/* Reserved                                    */
  .word	HSEM1_IRQHandler                 			/* HSEM global interrupt 2                     */
  .word	ADC3_IRQHandler                  			/* ADC3 global interrupt                       */
  .word	DMAMUX2_OVR_IRQHandler           			/* DMAMUX2 overrun interrupt                   */
  .word	BDMA_CH1_IRQHandler              			/* BDMA channel 1 interrupt                    */
  .word	BDMA_CH2_IRQHandler              			/* BDMA channel 2 interrupt                    */
  .word	BDMA_CH3_IRQHandler              			/* BDMA channel 3 interrupt                    */
  .word	BDMA_CH4_IRQHandler              			/* BDMA channel 4 interrupt                    */
  .word	BDMA_CH5_IRQHandler              			/* BDMA channel 5 interrupt                    */
  .word	BDMA_CH6_IRQHandler              			/* BDMA channel 6 interrupt                    */
  .word	BDMA_CH7_IRQHandler              			/* BDMA channel 7 interrupt                    */
  .word	BDMA_CH8_IRQHandler              			/* BDMA channel 8 interrupt                    */
  .word	COMP_IRQHandler                  			/* COMP1 and COMP2                             */
  .word	LPTIM2_IRQHandler                			/* LPTIM2 timer interrupt                      */
  .word	LPTIM3_IRQHandler                			/* LPTIM2 timer interrupt                      */
  .word	LPTIM4_IRQHandler                			/* LPTIM2 timer interrupt                      */
  .word	LPTIM5_IRQHandler                			/* LPTIM2 timer interrupt                      */
  .word	LPUART_IRQHandler                			/* LPUART global interrupt                     */
  .word	WWDG1_RST_IRQHandler             			/* Window Watchdog interrupt                   */
  .word	CRS_IRQHandler                   			/* Clock Recovery System globa                 */
  .word	0                                			/* Reserved                                    */
  .word	SAI4_IRQHandler                  			/* SAI4 global interrupt                       */
  .word	0                                			/* Reserved                                    */
  .word	HOLD_CORE_IRQHandler             			/* CPU2 hold                                   */
  .word	WKUP_IRQHandler                  			/* WKUP1 to WKUP6 pins                         */
  .size g_pfnVectors, .-g_pfnVectors

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

	.weak	NMI_Handler
	.thumb_set NMI_Handler,Default_Handler

	.weak	HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler

	.weak	MemManage_Handler
	.thumb_set MemManage_Handler,Default_Handler

	.weak	BusFault_Handler
	.thumb_set BusFault_Handler,Default_Handler

	.weak	UsageFault_Handler
	.thumb_set UsageFault_Handler,Default_Handler

	.weak	SVC_Handler
	.thumb_set SVC_Handler,Default_Handler

	.weak	DebugMon_Handler
	.thumb_set DebugMon_Handler,Default_Handler

	.weak	PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler

	.weak	SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler

	.weak	WWDG2_IRQHandler
	.thumb_set WWDG2_IRQHandler,Default_Handler

	.weak	PVD_PVM_IRQHandler
	.thumb_set PVD_PVM_IRQHandler,Default_Handler

	.weak	RTC_TAMP_STAMP_CSS_LSE_IRQHandler
	.thumb_set RTC_TAMP_STAMP_CSS_LSE_IRQHandler,Default_Handler

	.weak	RTC_WKUP_IRQHandler
	.thumb_set RTC_WKUP_IRQHandler,Default_Handler

	.weak	FLASH_IRQHandler
	.thumb_set FLASH_IRQHandler,Default_Handler

	.weak	RCC_IRQHandler
	.thumb_set RCC_IRQHandler,Default_Handler

	.weak	EXTI0_IRQHandler
	.thumb_set EXTI0_IRQHandler,Default_Handler

	.weak	EXTI1_IRQHandler
	.thumb_set EXTI1_IRQHandler,Default_Handler

	.weak	EXTI2_IRQHandler
	.thumb_set EXTI2_IRQHandler,Default_Handler

	.weak	EXTI3_IRQHandler
	.thumb_set EXTI3_IRQHandler,Default_Handler

	.weak	EXTI4_IRQHandler
	.thumb_set EXTI4_IRQHandler,Default_Handler

	.weak	DMA_STR0_IRQHandler
	.thumb_set DMA_STR0_IRQHandler,Default_Handler

	.weak	DMA_STR1_IRQHandler
	.thumb_set DMA_STR1_IRQHandler,Default_Handler

	.weak	DMA_STR2_IRQHandler
	.thumb_set DMA_STR2_IRQHandler,Default_Handler

	.weak	DMA_STR3_IRQHandler
	.thumb_set DMA_STR3_IRQHandler,Default_Handler

	.weak	DMA_STR4_IRQHandler
	.thumb_set DMA_STR4_IRQHandler,Default_Handler

	.weak	DMA_STR5_IRQHandler
	.thumb_set DMA_STR5_IRQHandler,Default_Handler

	.weak	DMA_STR6_IRQHandler
	.thumb_set DMA_STR6_IRQHandler,Default_Handler

	.weak	ADC1_2_IRQHandler
	.thumb_set ADC1_2_IRQHandler,Default_Handler

	.weak	FDCAN1_IT0_IRQHandler
	.thumb_set FDCAN1_IT0_IRQHandler,Default_Handler

	.weak	FDCAN2_IT0_IRQHandler
	.thumb_set FDCAN2_IT0_IRQHandler,Default_Handler

	.weak	FDCAN1_IT1_IRQHandler
	.thumb_set FDCAN1_IT1_IRQHandler,Default_Handler

	.weak	FDCAN2_IT1_IRQHandler
	.thumb_set FDCAN2_IT1_IRQHandler,Default_Handler

	.weak	EXTI9_5_IRQHandler
	.thumb_set EXTI9_5_IRQHandler,Default_Handler

	.weak	TIM1_BRK_IRQHandler
	.thumb_set TIM1_BRK_IRQHandler,Default_Handler

	.weak	TIM1_UP_IRQHandler
	.thumb_set TIM1_UP_IRQHandler,Default_Handler

	.weak	TIM1_TRG_COM_IRQHandler
	.thumb_set TIM1_TRG_COM_IRQHandler,Default_Handler

	.weak	TIM_CC_IRQHandler
	.thumb_set TIM_CC_IRQHandler,Default_Handler

	.weak	TIM2_IRQHandler
	.thumb_set TIM2_IRQHandler,Default_Handler

	.weak	TIM3_IRQHandler
	.thumb_set TIM3_IRQHandler,Default_Handler

	.weak	TIM4_IRQHandler
	.thumb_set TIM4_IRQHandler,Default_Handler

	.weak	I2C1_EV_IRQHandler
	.thumb_set I2C1_EV_IRQHandler,Default_Handler

	.weak	I2C1_ER_IRQHandler
	.thumb_set I2C1_ER_IRQHandler,Default_Handler

	.weak	I2C2_EV_IRQHandler
	.thumb_set I2C2_EV_IRQHandler,Default_Handler

	.weak	I2C2_ER_IRQHandler
	.thumb_set I2C2_ER_IRQHandler,Default_Handler

	.weak	SPI1_IRQHandler
	.thumb_set SPI1_IRQHandler,Default_Handler

	.weak	SPI2_IRQHandler
	.thumb_set SPI2_IRQHandler,Default_Handler

	.weak	USART1_IRQHandler
	.thumb_set USART1_IRQHandler,Default_Handler

	.weak	USART2_IRQHandler
	.thumb_set USART2_IRQHandler,Default_Handler

	.weak	USART3_IRQHandler
	.thumb_set USART3_IRQHandler,Default_Handler

	.weak	EXTI15_10_IRQHandler
	.thumb_set EXTI15_10_IRQHandler,Default_Handler

	.weak	RTC_ALARM_IRQHandler
	.thumb_set RTC_ALARM_IRQHandler,Default_Handler

	.weak	TIM8_BRK_TIM12_IRQHandler
	.thumb_set TIM8_BRK_TIM12_IRQHandler,Default_Handler

	.weak	TIM8_UP_TIM13_IRQHandler
	.thumb_set TIM8_UP_TIM13_IRQHandler,Default_Handler

	.weak	TIM8_TRG_COM_TIM14_IRQHandler
	.thumb_set TIM8_TRG_COM_TIM14_IRQHandler,Default_Handler

	.weak	TIM8_CC_IRQHandler
	.thumb_set TIM8_CC_IRQHandler,Default_Handler

	.weak	DMA1_STR7_IRQHandler
	.thumb_set DMA1_STR7_IRQHandler,Default_Handler

	.weak	FMC_IRQHandler
	.thumb_set FMC_IRQHandler,Default_Handler

	.weak	SDMMC1_IRQHandler
	.thumb_set SDMMC1_IRQHandler,Default_Handler

	.weak	TIM5_IRQHandler
	.thumb_set TIM5_IRQHandler,Default_Handler

	.weak	SPI3_IRQHandler
	.thumb_set SPI3_IRQHandler,Default_Handler

	.weak	UART4_IRQHandler
	.thumb_set UART4_IRQHandler,Default_Handler

	.weak	UART5_IRQHandler
	.thumb_set UART5_IRQHandler,Default_Handler

	.weak	TIM6_DAC_IRQHandler
	.thumb_set TIM6_DAC_IRQHandler,Default_Handler

	.weak	TIM7_IRQHandler
	.thumb_set TIM7_IRQHandler,Default_Handler

	.weak	DMA2_STR0_IRQHandler
	.thumb_set DMA2_STR0_IRQHandler,Default_Handler

	.weak	DMA2_STR1_IRQHandler
	.thumb_set DMA2_STR1_IRQHandler,Default_Handler

	.weak	DMA2_STR2_IRQHandler
	.thumb_set DMA2_STR2_IRQHandler,Default_Handler

	.weak	DMA2_STR3_IRQHandler
	.thumb_set DMA2_STR3_IRQHandler,Default_Handler

	.weak	DMA2_STR4_IRQHandler
	.thumb_set DMA2_STR4_IRQHandler,Default_Handler

	.weak	ETH_IRQHandler
	.thumb_set ETH_IRQHandler,Default_Handler

	.weak	ETH_WKUP_IRQHandler
	.thumb_set ETH_WKUP_IRQHandler,Default_Handler

	.weak	FDCAN_CAL_IRQHandler
	.thumb_set FDCAN_CAL_IRQHandler,Default_Handler

	.weak	cm7_sev_it_IRQHandler
	.thumb_set cm7_sev_it_IRQHandler,Default_Handler

	.weak	DMA2_STR5_IRQHandler
	.thumb_set DMA2_STR5_IRQHandler,Default_Handler

	.weak	DMA2_STR6_IRQHandler
	.thumb_set DMA2_STR6_IRQHandler,Default_Handler

	.weak	DMA2_STR7_IRQHandler
	.thumb_set DMA2_STR7_IRQHandler,Default_Handler

	.weak	USART6_IRQHandler
	.thumb_set USART6_IRQHandler,Default_Handler

	.weak	I2C3_EV_IRQHandler
	.thumb_set I2C3_EV_IRQHandler,Default_Handler

	.weak	I2C3_ER_IRQHandler
	.thumb_set I2C3_ER_IRQHandler,Default_Handler

	.weak	OTG_HS_EP1_OUT_IRQHandler
	.thumb_set OTG_HS_EP1_OUT_IRQHandler,Default_Handler

	.weak	OTG_HS_EP1_IN_IRQHandler
	.thumb_set OTG_HS_EP1_IN_IRQHandler,Default_Handler

	.weak	OTG_HS_WKUP_IRQHandler
	.thumb_set OTG_HS_WKUP_IRQHandler,Default_Handler

	.weak	OTG_HS_IRQHandler
	.thumb_set OTG_HS_IRQHandler,Default_Handler

	.weak	DCMI_IRQHandler
	.thumb_set DCMI_IRQHandler,Default_Handler

	.weak	HASH_RNG_IRQHandler
	.thumb_set HASH_RNG_IRQHandler,Default_Handler

	.weak	FPU_IRQHandler
	.thumb_set FPU_IRQHandler,Default_Handler

	.weak	UART7_IRQHandler
	.thumb_set UART7_IRQHandler,Default_Handler

	.weak	UART8_IRQHandler
	.thumb_set UART8_IRQHandler,Default_Handler

	.weak	SPI4_IRQHandler
	.thumb_set SPI4_IRQHandler,Default_Handler

	.weak	SPI5_IRQHandler
	.thumb_set SPI5_IRQHandler,Default_Handler

	.weak	SPI6_IRQHandler
	.thumb_set SPI6_IRQHandler,Default_Handler

	.weak	SAI1_IRQHandler
	.thumb_set SAI1_IRQHandler,Default_Handler

	.weak	LTDC_IRQHandler
	.thumb_set LTDC_IRQHandler,Default_Handler

	.weak	LTDC_ER_IRQHandler
	.thumb_set LTDC_ER_IRQHandler,Default_Handler

	.weak	DMA2D_IRQHandler
	.thumb_set DMA2D_IRQHandler,Default_Handler

	.weak	SAI2_IRQHandler
	.thumb_set SAI2_IRQHandler,Default_Handler

	.weak	QUADSPI_IRQHandler
	.thumb_set QUADSPI_IRQHandler,Default_Handler

	.weak	LPTIM1_IRQHandler
	.thumb_set LPTIM1_IRQHandler,Default_Handler

	.weak	CEC_IRQHandler
	.thumb_set CEC_IRQHandler,Default_Handler

	.weak	I2C4_EV_IRQHandler
	.thumb_set I2C4_EV_IRQHandler,Default_Handler

	.weak	I2C4_ER_IRQHandler
	.thumb_set I2C4_ER_IRQHandler,Default_Handler

	.weak	SPDIF_IRQHandler
	.thumb_set SPDIF_IRQHandler,Default_Handler

	.weak	OTG_FS_EP1_OUT_IRQHandler
	.thumb_set OTG_FS_EP1_OUT_IRQHandler,Default_Handler

	.weak	OTG_FS_EP1_IN_IRQHandler
	.thumb_set OTG_FS_EP1_IN_IRQHandler,Default_Handler

	.weak	OTG_FS_WKUP_IRQHandler
	.thumb_set OTG_FS_WKUP_IRQHandler,Default_Handler

	.weak	OTG_FS_IRQHandler
	.thumb_set OTG_FS_IRQHandler,Default_Handler

	.weak	DMAMUX1_OV_IRQHandler
	.thumb_set DMAMUX1_OV_IRQHandler,Default_Handler

	.weak	HRTIM1_MST_IRQHandler
	.thumb_set HRTIM1_MST_IRQHandler,Default_Handler

	.weak	HRTIM1_TIMA_IRQHandler
	.thumb_set HRTIM1_TIMA_IRQHandler,Default_Handler

	.weak	HRTIM_TIMB_IRQHandler
	.thumb_set HRTIM_TIMB_IRQHandler,Default_Handler

	.weak	HRTIM1_TIMC_IRQHandler
	.thumb_set HRTIM1_TIMC_IRQHandler,Default_Handler

	.weak	HRTIM1_TIMD_IRQHandler
	.thumb_set HRTIM1_TIMD_IRQHandler,Default_Handler

	.weak	HRTIM_TIME_IRQHandler
	.thumb_set HRTIM_TIME_IRQHandler,Default_Handler

	.weak	HRTIM1_FLT_IRQHandler
	.thumb_set HRTIM1_FLT_IRQHandler,Default_Handler

	.weak	DFSDM1_FLT0_IRQHandler
	.thumb_set DFSDM1_FLT0_IRQHandler,Default_Handler

	.weak	DFSDM1_FLT1_IRQHandler
	.thumb_set DFSDM1_FLT1_IRQHandler,Default_Handler

	.weak	DFSDM1_FLT2_IRQHandler
	.thumb_set DFSDM1_FLT2_IRQHandler,Default_Handler

	.weak	DFSDM1_FLT3_IRQHandler
	.thumb_set DFSDM1_FLT3_IRQHandler,Default_Handler

	.weak	SAI3_IRQHandler
	.thumb_set SAI3_IRQHandler,Default_Handler

	.weak	SWPMI1_IRQHandler
	.thumb_set SWPMI1_IRQHandler,Default_Handler

	.weak	TIM15_IRQHandler
	.thumb_set TIM15_IRQHandler,Default_Handler

	.weak	TIM16_IRQHandler
	.thumb_set TIM16_IRQHandler,Default_Handler

	.weak	TIM17_IRQHandler
	.thumb_set TIM17_IRQHandler,Default_Handler

	.weak	MDIOS_WKUP_IRQHandler
	.thumb_set MDIOS_WKUP_IRQHandler,Default_Handler

	.weak	MDIOS_IRQHandler
	.thumb_set MDIOS_IRQHandler,Default_Handler

	.weak	JPEG_IRQHandler
	.thumb_set JPEG_IRQHandler,Default_Handler

	.weak	MDMA_IRQHandler
	.thumb_set MDMA_IRQHandler,Default_Handler

	.weak	SDMMC_IRQHandler
	.thumb_set SDMMC_IRQHandler,Default_Handler

	.weak	HSEM1_IRQHandler
	.thumb_set HSEM1_IRQHandler,Default_Handler

	.weak	ADC3_IRQHandler
	.thumb_set ADC3_IRQHandler,Default_Handler

	.weak	DMAMUX2_OVR_IRQHandler
	.thumb_set DMAMUX2_OVR_IRQHandler,Default_Handler

	.weak	BDMA_CH1_IRQHandler
	.thumb_set BDMA_CH1_IRQHandler,Default_Handler

	.weak	BDMA_CH2_IRQHandler
	.thumb_set BDMA_CH2_IRQHandler,Default_Handler

	.weak	BDMA_CH3_IRQHandler
	.thumb_set BDMA_CH3_IRQHandler,Default_Handler

	.weak	BDMA_CH4_IRQHandler
	.thumb_set BDMA_CH4_IRQHandler,Default_Handler

	.weak	BDMA_CH5_IRQHandler
	.thumb_set BDMA_CH5_IRQHandler,Default_Handler

	.weak	BDMA_CH6_IRQHandler
	.thumb_set BDMA_CH6_IRQHandler,Default_Handler

	.weak	BDMA_CH7_IRQHandler
	.thumb_set BDMA_CH7_IRQHandler,Default_Handler

	.weak	BDMA_CH8_IRQHandler
	.thumb_set BDMA_CH8_IRQHandler,Default_Handler

	.weak	COMP_IRQHandler
	.thumb_set COMP_IRQHandler,Default_Handler

	.weak	LPTIM2_IRQHandler
	.thumb_set LPTIM2_IRQHandler,Default_Handler

	.weak	LPTIM3_IRQHandler
	.thumb_set LPTIM3_IRQHandler,Default_Handler

	.weak	LPTIM4_IRQHandler
	.thumb_set LPTIM4_IRQHandler,Default_Handler

	.weak	LPTIM5_IRQHandler
	.thumb_set LPTIM5_IRQHandler,Default_Handler

	.weak	LPUART_IRQHandler
	.thumb_set LPUART_IRQHandler,Default_Handler

	.weak	WWDG1_RST_IRQHandler
	.thumb_set WWDG1_RST_IRQHandler,Default_Handler

	.weak	CRS_IRQHandler
	.thumb_set CRS_IRQHandler,Default_Handler

	.weak	SAI4_IRQHandler
	.thumb_set SAI4_IRQHandler,Default_Handler

	.weak	HOLD_CORE_IRQHandler
	.thumb_set HOLD_CORE_IRQHandler,Default_Handler

	.weak	WKUP_IRQHandler
	.thumb_set WKUP_IRQHandler,Default_Handler

	.weak	SystemInit

/************************ (C) COPYRIGHT STMicroelectonics *****END OF FILE****/
