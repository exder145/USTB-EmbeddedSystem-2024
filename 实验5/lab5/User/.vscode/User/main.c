#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_systick.h"


int main(void)
{
	// LED的GPIO初始化。
	LED_GPIO_Config();
	
	while(1)
	{
		// 熄灭LED
		LED_G(OFF);
		// 延时1s
		SysTick_Delay_ms(1000);
		// 点亮LED
		LED_G(ON);
		// 延时1s
		SysTick_Delay_us(1000000);
	}
}





