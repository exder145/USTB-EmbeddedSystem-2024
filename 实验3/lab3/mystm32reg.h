// �������STM32�Ĵ���ӳ��Ĵ���

// ����  perirhral

#define  PERIPH_BASE               ((unsigned int)0x40000000)
#define  APB1PERIPH_BASE           PERIPH_BASE
#define  APB2PERIPH_BASE          (PERIPH_BASE + 0x10000)
#define  AHBPERIPH_BASE           (PERIPH_BASE + 0x20000)


#define  RCC_BASE                (AHBPERIPH_BASE + 0x1000)
#define  RCC_APB2ENR            *(unsigned int*)(RCC_BASE + 0x18)
	
//��Ӵ���

// ��� GPIOA �Ķ���
#define GPIOA_BASE               (APB2PERIPH_BASE + 0x0800)  // GPIOA ����ַ
#define GPIOA_CRL                *(unsigned int *)(GPIOA_BASE + 0x00)  // ���ƼĴ���
#define GPIOA_IDR                *(unsigned int *)(GPIOA_BASE + 0x08)  // �������ݼĴ���

//��� GPIOB �Ķ���
#define GPIOB_BASE              (APB2PERIPH_BASE + 0x0C00)  // GPIOB ����ַ
#define GPIOB_CRL               *(unsigned int *)(GPIOB_BASE + 0x00)  // ���ƼĴ���
#define GPIOB_ODR               *(unsigned int *)(GPIOB_BASE + 0x0C)  // ������ݼĴ���

	



