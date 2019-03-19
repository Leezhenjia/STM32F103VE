#include "includes.h"


/*
 *	������	:	SysTick_init
 *	����	:	���� SysTick ��ʱ��
 *	����	:	��
 *	���	:	��
 */

void SysTick_init(void)
{
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);	//��ʼ����ʹ��	SysTick	��ʱ��SystemFrequency
}

/*
 *	������	:	BSPInit
 *	����	:	ʱ�ӳ�ʼ��,Ӳ����ʼ��
 *	����	:	��
 *	���	:	��
 */
 
void BSPInit(void)
{
	SystemInit();		//����ϵͳʱ��Ϊ72M
	SysTick_init();;	//��ʼ����ʹ�� Systick ��ʱ��
	LED_GPIO_Config();	//LED�˿ڳ�ʼ��
    TIM7Init();         //��ʱ����ʼ��
    ILI9341_Init();    //LCD ��ʼ��
    XPT2046_Init();     //��������ʼ��
    Calibrate_or_Get_TouchParaWithFlash(6,0);//��FLASH���ȡУ����������FLASH�޲�������ʹ��ģʽ6����У��
	USART_Config();     //���ڳ�ʼ��
    ILI9341_GramScan(6);//��ʾ��ģʽ
	Palette_HomeInit(LCD_SCAN_MODE);//���ƴ����������
}

