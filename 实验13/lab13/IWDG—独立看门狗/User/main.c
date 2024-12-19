#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_iwdg.h"

static void Delay(__IO u32 nCount);

/**
 * @brief  主函数
 * @param  无
 * @retval 无
 */
int main(void)
{
	// 初始化LED的GPIO，并关闭LED
	LED_GPIO_Config();

	Delay(0X2FFFFF);
	/*------------------------------------------------------------*/
	/* 检测是否为看门狗复位 */
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		/* 如果是看门狗复位 */
		/* 点亮红灯 */
		LED_RED;

		/* 清除标志 */
		RCC_ClearFlag();

		/* 如果一直不喂狗，会一直复位，如果前面的延时过长，就会看到红灯闪烁
		   超过1s时间不喂狗的话，就会导致系统复位 */
	}
	else
	{
		/* 如果不是看门狗复位(可能为上电复位或者手动按键复位之类的) */
		/* 点亮蓝灯 */
		LED_BLUE;
	}
	/*--------------------------------------------------------------*/

	// 初始化按键GPIO
	Key_GPIO_Config();
	// 修改为1秒超时
	// Tout = prv/40 * rlv (s)
	// 1 = 64/40 * 625
	IWDG_Config(IWDG_Prescaler_64, 625); // 设置1秒超时

	// while里面要写代码，外部值的操作看门狗
	// 知道外部执行执行时间，500ms左右就要喂看门狗
	// 时间600ms和500ms一样，要看代码中有没有执行很长的代码
	// 执行之后会执行喂狗的操作，非常容易会超时不喂狗
	// 某些时候会系统复位也有可能会有，及时喂狗了
	// 所以要确认了程序运行，才使用看门狗看门狗设定
	// 设定的时候喂狗
	while (1)
	{
		///// 按键测试开始
		if (Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON)
		{
			IWDG_Feed(); // 按下KEY1喂狗
			LED_GREEN;	 // 喂狗成功则亮绿灯
		}
		///// 按键测试结束
	}
	//---------------------------------------------------------------------------
}

static void Delay(__IO uint32_t nCount) // 简单的延时函数
{
	for (; nCount != 0; nCount--)
		;
}

/*********************************************文件结束**********************/
