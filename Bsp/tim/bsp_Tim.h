#ifndef __BSP_TIME_H
#define __BSP_TIME_H


#include "stm32f10x.h"


/********************������ʱ��TIM�������壬ֻ��TIM6 7************/
/*
 *	prescaler����Ƶ��
 *	period������������
 */
#if 0
// ��ʱ��TIM6
#define            BASIC_TIM6                   TIM6
#define            BASIC_TIM6_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM6_CLK               RCC_APB1Periph_TIM6
#define            BASIC_TIM6_Period            57
#define            BASIC_TIM6_Prescaler         720-1
#define            BASIC_TIM6_IRQ               TIM6_IRQn
#define            BASIC_TIM6_IRQHandler        TIM6_IRQHandler
#else
// ��ʱ��TIM7
#define            BASIC_TIM7                   TIM7
#define            BASIC_TIM7_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM7_CLK               RCC_APB1Periph_TIM7
#define            BASIC_TIM7_Period            57
#define            BASIC_TIM7_Prescaler         720-1
#define            BASIC_TIM7_IRQ               TIM7_IRQn
#define            BASIC_TIM7_IRQHandler        TIM7_IRQHandler
#endif

/**************************��������********************************/

void TIM7Init(void);


#endif	/* __BSP_TIME_H */


