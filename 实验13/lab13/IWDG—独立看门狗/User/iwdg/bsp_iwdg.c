
#include "bsp_iwdg.h"

/*
 * ���� IWDG �ĳ�ʱʱ��
 * Tout = prv/40 * rlv (s)
 *      prv������[4,8,16,32,64,128,256]
 * prv:Ԥ��Ƶ��ֵ��ȡֵ���£�
 *     @arg IWDG_Prescaler_4: IWDG prescaler set to 4
 *     @arg IWDG_Prescaler_8: IWDG prescaler set to 8
 *     @arg IWDG_Prescaler_16: IWDG prescaler set to 16
 *     @arg IWDG_Prescaler_32: IWDG prescaler set to 32
 *     @arg IWDG_Prescaler_64: IWDG prescaler set to 64
 *     @arg IWDG_Prescaler_128: IWDG prescaler set to 128
 *     @arg IWDG_Prescaler_256: IWDG prescaler set to 256
 *
 * rlv:��װ�ؼĴ���ֵ��ȡֵ��ΧΪ��0-0XFFF
 * �������þ�����
 * IWDG_Config(IWDG_Prescaler_64 ,625);  // IWDG 1s ��ʱ���
 */

void IWDG_Config(uint8_t prv, uint16_t rlv)
{
	// 使能 IWDG
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

	// 设置预分频器
	IWDG_SetPrescaler(prv);

	// 设置重装载值
	IWDG_SetReload(rlv);

	// 重载IWDG计数器
	IWDG_ReloadCounter();

	// 使能IWDG
	IWDG_Enable();
}

// ι��
void IWDG_Feed(void)
{
	// ����װ�ؼĴ�����ֵ�ŵ��������У�ι������ֹIWDG��λ
	// ����������ֵ����0��ʱ������ϵͳ��λ
	IWDG_ReloadCounter();
}

/*********************************************END OF FILE**********************/
