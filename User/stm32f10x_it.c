/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_it.h"
#include "includes.h"


extern OS_EVENT *Usart_Send_Mbox;
extern OS_EVENT *Tim6_Analysis_Mbox;
volatile uint32_t time = 0; //�ַ�ʱ�����

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	OSIntEnter();
	OSTimeTick();
	OSIntExit();
}

/************************************************************************
    ���ߣ� lizhenjia 
    �������ڣ�2019.3.15 
    ��������˵���� USART�жϺ���,���ѽ�������
    ��������� ��
    �������ƣ���
    ��������� ��������
    �������ƣ�ucTemp
    ����ֵ�� ��
    �����ȳ��嵥�� 
    ���������嵥�� 
    ���������õ��Ĺ�����Դ��
    ���º��������Դ�� 
*************************************************************************/
void DEBUG_USART_IRQHandler(void)
{
    uint8_t ucTemp;
    
    OSIntEnter();
	if (USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE) != RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USARTx);//��ȡ���յ����ֽ�
        OSMboxPost(Usart_Send_Mbox, (void *)&ucTemp);   //���͸���������
	}	
    OSIntExit();    
}

/************************************************************************
    ���ߣ� lizhenjia 
    �������ڣ�2019.3.15 
    ��������˵���� �ַ�ʱ�䶨ʱ
    ��������� ��
    �������ƣ���
    ��������� ��
    �������ƣ���
    ����ֵ�� ��
    �����ȳ��嵥�� 
    ���������嵥�� 
    ���������õ��Ĺ�����Դ��
    ���º��������Դ�� 
*************************************************************************/
void  BASIC_TIM6_IRQHandler(void)
{
    OSIntEnter();
	if (TIM_GetITStatus(BASIC_TIM6, TIM_IT_Update) != RESET )
	{
		TIM_ClearITPendingBit(BASIC_TIM6, TIM_FLAG_Update);
		time++;
        LED1_ON;
		if (time > 7)
		{
			BASIC_TIM6_APBxClock_FUN(BASIC_TIM6_CLK, DISABLE);//����3.5�ַ�ʱ�䲻�ٽ���,�ر��ַ��ۼƼ�ʱ
			time = 0;
            OSMboxPost(Tim6_Analysis_Mbox, (void *)1);   //���͸���������
		}
	}
    OSIntExit();
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/