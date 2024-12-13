#include "bsp_GeneralTim.h"

/* 声明外部变量 */
extern uint8_t cur_ch;

static void GENERAL_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// 重映射TIM3_CH2到PB5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

	// 根据当前通道配置对应的GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	switch (cur_ch)
	{
	case 2:
		RCC_APB2PeriphClockCmd(GENERAL_TIM_CH2_GPIO_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GENERAL_TIM_CH2_PIN;
		GPIO_Init(GENERAL_TIM_CH2_PORT, &GPIO_InitStructure);
		break;
	case 3:
		RCC_APB2PeriphClockCmd(GENERAL_TIM_CH3_GPIO_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GENERAL_TIM_CH3_PIN;
		GPIO_Init(GENERAL_TIM_CH3_PORT, &GPIO_InitStructure);
		break;
	case 4:
		RCC_APB2PeriphClockCmd(GENERAL_TIM_CH4_GPIO_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GENERAL_TIM_CH4_PIN;
		GPIO_Init(GENERAL_TIM_CH4_PORT, &GPIO_InitStructure);
		break;
	}
}

///*
// * 注：TIM_TimeBaseInitTypeDef结构体5个成员TIM6TIM7没��
// * TIM_PrescalerTIM_Period只有TIM6TIM7使用
// * 其他定时器都不使用.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler
// *	TIM_CounterMode			     TIMx,x[6,7]没有
// *  TIM_Period
// *  TIM_ClockDivision        TIMx,x[6,7]没有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]
// *}TIM_TimeBaseInitTypeDef;
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM信号输出配置--------------- */
// ARR 寄存器的值
// CLK_cnt的频率 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 周期 = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)

static void GENERAL_TIM_Mode_Config(uint16_t chval)
{
	// 时钟,内部时钟CK_INT=72M
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);

	/*--------------------时基结构体-------------------------*/
	// 分频系数为100K

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period;
	// 时钟预分频数为
	TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM_Prescaler;
	// 时钟分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// 计数模式为向���计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// 重复计数器
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	// 初始化定时器
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体-------------------*/
	// 输出比较

	uint16_t CCR_Val = chval;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = CCR_Val;

	// 根据当前通道选择配置对应的PWM
	switch (cur_ch)
	{
	case 2:
		TIM_OC2Init(GENERAL_TIM, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
		break;
	case 3:
		TIM_OC3Init(GENERAL_TIM, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
		break;
	case 4:
		TIM_OC4Init(GENERAL_TIM, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
		break;
	}

	// 启动计数器
	TIM_Cmd(GENERAL_TIM, ENABLE);
}

void TIM_Stop(void)
{
	// 禁止计数器
	TIM_Cmd(GENERAL_TIM, DISABLE);
}

void GENERAL_TIM_Init(uint16_t chval)
{
	GENERAL_TIM_GPIO_Config();
	GENERAL_TIM_Mode_Config(chval);
}

/*********************************************END OF FILE**********************/
