
// ������ʱ��TIMx,x[6,7]��ʱ��ʼ������

#include "bsp_tim.h"

// �ж����ȼ�����
static void BASIC_TIM6_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM6_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ4
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


//����0.52ms����һ���ж�,��0.5�ַ�ʱ��

static void BASIC_TIM6_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    BASIC_TIM6_APBxClock_FUN(BASIC_TIM6_CLK, ENABLE);
	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM6_Period;	

	  // ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM6_Prescaler;
	
	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(BASIC_TIM6, &TIM_TimeBaseStructure);
		
		// ����������жϱ�־λ
    TIM_ClearFlag(BASIC_TIM6, TIM_FLAG_Update);
	 
		// �����������ж�
    TIM_ITConfig(BASIC_TIM6,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(BASIC_TIM6, ENABLE);	
    
    //��ʱ�رն�ʱ��ʱ��,�ȴ�ʹ��
	BASIC_TIM6_APBxClock_FUN(BASIC_TIM6_CLK, DISABLE);	
}



void TIM6Init(void)
{
	BASIC_TIM6_NVIC_Config();
	BASIC_TIM6_Mode_Config();
}
/*********************************************END OF FILE**********************/