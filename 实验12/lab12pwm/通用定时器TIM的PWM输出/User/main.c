// TIM��ͨ�ö�ʱ��-3·ѡ1·PWM���Ӧ��
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_GeneralTim.h"

// �����ʱ
void Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount--)
		;
}

// ��ǰѡ�е�PWMͨ������ʼΪͨ��4(����)
uint8_t cur_ch = 4;

/**
 * @brief  ������
 * @param  ��
 * @retval ��
 */
int main(void)
{
	// ռ�ձ����飬����LED���Ƚ���
	uint16_t ch_val[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	uint8_t idx = 0;
	uint16_t cur_chval;

	/* led �˿����� */
	LED_GPIO_Config();
	/* key�ⲿ�ж����� */
	EXIT_Key_Config();

	while (1)
	{
		cur_chval = ch_val[idx];
		/* ���ݵ�ǰѡ��ͨ����ʼ����ʱ�� */
		switch (cur_ch)
		{
		case 2:
			GENERAL_TIM_Init(cur_chval); // ��ʼ��CH2(���)
			break;
		case 3:
			GENERAL_TIM_Init(cur_chval); // ��ʼ��CH3(�̵�)
			break;
		case 4:
			GENERAL_TIM_Init(cur_chval); // ��ʼ��CH4(����)
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
