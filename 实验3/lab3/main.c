// coding: utf-8
#include "mystm32reg.h"

void SystemInit(void)
{
    // �˺����ᱻstartup�ļ����ã�
    // ������Ϊ�գ�Ŀ����Ϊ��ƭ��������������
}

int main(void)
{

    // ����PB0�����ϵ�Green��

    // �� GPIOB �˿ڵ�ʱ��
    RCC_APB2ENR |= ((1) << 3);

    // ����IO��PB0Ϊ���
    GPIOB_CRL |= ((1) << (4 * 0));

    // ���� ODR �Ĵ���,��PB0����������͵�ƽ������Green��
    GPIOB_ODR &= ~(1 << 0);

    // KEY1 is PA0, ��ʼ��PA0��GPIO����

    RCC_APB2ENR |= ((1) << 2); // ��GPIOA��ʱ��
    GPIOA_CRL &= ~(0x0F);      // ���PA0������
    GPIOA_CRL |= (0x04);       // ����PA0Ϊ���븡��ģʽ

    // KEY1 ������⣬���� G_LED ����

    while (1)
    {
        // ��� PA0 ��״̬
        if ((GPIOA_IDR & (1 << 0)) == 0) // ����������ʱ��PA0 Ϊ�͵�ƽ
        {
            // �л� PB0 ��״̬
            GPIOB_ODR ^= (1 << 0); // �л��Ƶ�״̬

            // �ȴ������ͷ�
            while ((GPIOA_IDR & (1 << 0)) == 0)
                ; // �ȴ� PA0 ��Ϊ�ߵ�ƽ
        }
    }
}
