
void delay(unsigned int cnt){
  
	while(cnt>=1)(cnt--);

  }


void SystemInit(void)
{
	// �˺����ᱻstartup�ļ����ã�
	// ������Ϊ�գ�Ŀ����Ϊ��ƭ��������������
}



int main(void) {
    // �� GPIOB �˿ڵ�ʱ��
    *(unsigned int *)0x40021018 |= (1 << 3);

    // ����IO��PB0��PB1��PB2Ϊ���
    *(unsigned int *)0x40010C00 |= (1 << (4 * 0)); // PB0����Ϊ���


    // ����PB0�����ϵ�Green��
    *(unsigned int *)0x40010C0C &= ~(1 << 0);
    delay(1000000); // ��ʱ
	
    // �ر�PB0�����ϵ�Green��
    *(unsigned int *)0x40010C0C |= (1 << 0);
    delay(1000000); // ��ʱ
	
    // ����PB1�����ϵ�Blue��
	  *(unsigned int *)0x40010C00 |= (1 << (4 * 1)); // PB1����Ϊ���
	
    *(unsigned int *)0x40010C0C &= ~(1 << 1);
    delay(1000000); // ��ʱ
	
    // �ر�PB1�����ϵ�Blue��
    *(unsigned int *)0x40010C0C |= (1 << 1);
    delay(1000000); // ��ʱ
		
		// ����PB2�����ϵ�Red��
		*(unsigned int *)0x40010C00 |= (1 << (4 * 5)); // PB2����Ϊ���
				
    *(unsigned int *)0x40010C0C &= ~(1 << 5);
    delay(1000000); // ��ʱ
		
    // �ر�PB2�����ϵ�Red��
    *(unsigned int *)0x40010C0C |= (1 << 5);
    delay(1000000); // ��ʱ
		
    return 0;
}




// ѧ����������ܣ�
// 1�� �������ֲ���ҼĴ����ľ��Ե�ַ
// 2�� ѧ��ԼĴ������ض�λ������1(Ҳ����λ��set)����0(Ҳ����0,clr)��������λ:   |= ��mask)   ����0: &=~��mask)

// 1������/Ϩ������������LED��
