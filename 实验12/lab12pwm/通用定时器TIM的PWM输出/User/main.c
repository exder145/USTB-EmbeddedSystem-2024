// TIM—通用定时器-3路选1路PWM输出应用
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_GeneralTim.h"

// 软件延时
void Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount--)
		;
}

// 当前选中的PWM通道，初始为通道4(蓝灯)
uint8_t cur_ch = 4;

/**
 * @brief  主函数
 * @param  无
 * @retval 无
 */
int main(void)
{
	// 占空比数组，用于LED亮度渐变
	uint16_t ch_val[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	uint8_t idx = 0;
	uint16_t cur_chval;

	/* led 端口配置 */
	LED_GPIO_Config();
	/* key外部中断设置 */
	EXIT_Key_Config();

	while (1)
	{
		cur_chval = ch_val[idx];
		/* 根据当前选中通道初始化定时器 */
		switch (cur_ch)
		{
		case 2:
			GENERAL_TIM_Init(cur_chval); // 初始化CH2(红灯)
			break;
		case 3:
			GENERAL_TIM_Init(cur_chval); // 初始化CH3(绿灯)
			break;
		case 4:
			GENERAL_TIM_Init(cur_chval); // 初始化CH4(蓝灯)
			break;
		}
		idx++;
		if (idx >= 18)
			idx = 0;
		Delay(0xffffee);
		TIM_Stop();
	}
}
/*********************************************END OF FILE**********************/
