#include "stm32f10x.h"
#include "bsp_led.h"

#include "bsp_exti.h"

extern int i; // 确保 i 只在一个文件中定义

#define SOFT_DELAY Delay(0x0FFFFF);

void Delay(__IO u32 nCount);

int main(void)
{
	// ʱϵͳʱѾó72M
	LED_GPIO_Config();

i = 1;

	EXIT_Key_Config();

	while (1)
	{
		switch (i % 3)
		{

		case 0:
			LED1_ON; //
			SOFT_DELAY;
			LED1_OFF; //
			SOFT_DELAY;
			break;
		case 1:
			LED2_ON; //
			SOFT_DELAY;
			LED2_OFF; //
			SOFT_DELAY;
			break;
		case 2:
			LED3_ON; //
			SOFT_DELAY;
			LED3_OFF; //
			SOFT_DELAY;
			break;
		default:
			continue;
		}
	}
}

void Delay(__IO uint32_t nCount) // 򵥵ʱ
{
	for (; nCount != 0; nCount--)
		;
}
