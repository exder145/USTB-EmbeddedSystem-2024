#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_systick.h"


int main(void)
{
	// LED��GPIO��ʼ����
	LED_GPIO_Config();
	
	while(1)
	{
		// Ϩ��LED
		LED_G(OFF);
		// ��ʱ1s
		SysTick_Delay_ms(1000);
		// ����LED
		LED_G(ON);
		// ��ʱ1s
		SysTick_Delay_us(1000000);
	}
}





