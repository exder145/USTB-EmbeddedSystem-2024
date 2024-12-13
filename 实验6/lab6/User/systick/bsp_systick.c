// bsp_SysTick.c
#include "bsp_SysTick.h"
#include "core_cm3.h"
#include "misc.h"
/**
 * @brief 启动系统滴答定时器 SysTick
 * @param 无
 * @retval 无
 */

static __IO u32 TimingDelay;

/**
* @brief us 延时程序,10us 为一个单位
* @param
* @arg nTime: Delay_us( 1 ) 则实现的延时为
1 * 10us = 10us
* @retval 无
*/
void Delay_us(__IO u32 nTime)
{
	TimingDelay = nTime;
	while (TimingDelay != 0)
		;
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

void SysTick_Init(void)
{
	/* SystemCoreClock / 100000 10us中断一次
	 * SystemCoreClock / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock / 100000)) // ST3.5.0库版本
	{
		/* Capture error */
		while (1)
			;
	}
}