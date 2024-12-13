// main.c
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"
int main(void)
{
	/* LED 端口初始化 */
	LED_GPIO_Config();
	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();
	for (;;)
	{
		LED_G(ON);		  // 打开 LED
		Delay_us(100000); // 100000 * 10us = 1000ms
		LED_G(OFF);		  // 关闭 LED
		Delay_us(100000); // 100000 * 10us = 1000ms
	}
}
