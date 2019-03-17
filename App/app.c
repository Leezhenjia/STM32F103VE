/***************************************************************************
    ��Ȩ���У�lizhenjia
    �汾�ţ� 1.00 
    �ļ����� app.c 
    �������ڣ�2019.3.15 
    ���ߣ� lizhenjia 
    ����˵����uCOS II ����
    �����������ļ��Ĺ�ϵ�� �����ļ�
    ����˵������
    �޸ļ�¼��  ��
***************************************************************************/

#include "includes.h"


OS_STK send_task_stk[STARTUP_TASK_STK_SIZE]; 
OS_STK receive_task_stk[STARTUP_TASK_STK_SIZE]; 
OS_STK analysis_task_stk[STARTUP_TASK_STK_SIZE]; 
OS_STK disp_task_stk[STARTUP_TASK_STK_SIZE]; //�����ĸ�����ջ
 
OS_EVENT *Usart_Send_Mbox;  //����,��USART�յ����ݷ��͵�Receive����
OS_EVENT *Tim7_Analysis_Mbox;  //����,��ʱ��7֪ͨAnalysis����ʼ��������

extern volatile uint32_t time; //�ַ�ʱ�����
extern uint8_t RX_BUFF[2048];//���ջ�����
uint16_t RX_CNT = 0;    //�����ֽڼ���
extern uint16_t MasterRead[1000];//���յ�������
extern uint8_t EXCEPTION_CODE;

void Task_Start(void *p_arg)
{
	(void)p_arg;	//��ܱ���������
    
    Usart_Send_Mbox = OSMboxCreate((void *)0);
    Tim7_Analysis_Mbox = OSMboxCreate((void *)0);
    
#if OS_STK_GROWTH == 1
    OSTaskCreate(Task_Send, (void *)0, &send_task_stk[STARTUP_TASK_STK_SIZE - 1], SEND_TASK_PRIO);
    OSTaskCreate(Task_Receive, (void *)0, &receive_task_stk[STARTUP_TASK_STK_SIZE - 1], RECEIVE_TASK_PRIO);
    OSTaskCreate(Task_Analysis, (void *)0, &analysis_task_stk[STARTUP_TASK_STK_SIZE - 1], ANALYSIS_TASK_PRIO);
    OSTaskCreate(Task_Disp, (void *)0, &disp_task_stk[STARTUP_TASK_STK_SIZE - 1], DISP_TASK_PRIO);
#else
    OSTaskCreate(Task_Send, (void *)0, &send_task_stk[0], SEND_TASK_PRIO);
    OSTaskCreate(Task_Receive, (void *)0, &receive_task_stk[0], RECEIVE_TASK_PRIO);
    OSTaskCreate(Task_Analysis, (void *)0, &analysis_task_stk[0], ANALYSIS_TASK_PRIO);
    OSTaskCreate(Task_Disp, (void *)0, &disp_task_stk[0], DISP_TASK_PRIO);
#endif
    
	OSTaskDel(OS_PRIO_SELF);   //ɾ����ʼ����
}

void Task_Send(void *p_arg)
{
	(void)p_arg;	//��ܱ���������
	
	while (1)
	{
        ModbusRTU();    //��ʼ����ָ��
		OSTimeDlyHMSM(0, 0, 2, 0);  //����1s�ȴ����ս�������
	}
}

void Task_Receive(void *p_arg)
{
	uint8_t *Temp;
    uint8_t err = 0;
    
    
    (void)p_arg;	//��ܱ��������� 

    
	while (1)
	{
        Temp = (uint8_t *)OSMboxPend(Usart_Send_Mbox, 0, &err); //�ȴ�����USART�жϵ�������Ϣ
        if (RX_CNT < 2047 && time <= 3)
        {
            if (0 == RX_CNT)
            {
                BASIC_TIM7_APBxClock_FUN(BASIC_TIM7_CLK, ENABLE);//����TIM6��ʱ,�ۼ�֡���ʱ��
            }
            RX_BUFF[RX_CNT] = *Temp;
            RX_CNT++;
            time = 0;
        }
	}
}

void Task_Analysis(void *p_arg)
{
    uint8_t err;
    
    
	(void)p_arg;	//��ܱ���������
	
    
	while (1)
	{
        OSMboxPend(Tim7_Analysis_Mbox, 0, &err);    //�����������
        MasterAnalyService();   //��ʼ���� 
	}
}

void Task_Disp(void *p_arg)
{
    uint8_t i = 0;
    
    
	(void)p_arg;	//��ܱ���������
	
    
	while (1)
	{
        LCD_SetFont(&Font8x16);
        LCD_SetColors(RED, BLACK);
        ILI9341_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH);	/* ��������ʾȫ�� */
        ILI9341_DispStringLine_EN(LINE(0), "START RUNNING");
        /********��ʾ����ʾ��*******/
        LCD_SetFont(&Font16x24);
        LCD_SetTextColor(GREEN);

        switch (RX_BUFF[1])
        {
            case 3:
                for(i = 0; i < (RX_BUFF[2] / 2); i++)
                ILI9341_DispVariable_EN(LINE(i + 1), "REG:", MasterRead[i]);
                if(EXCEPTION_CODE != 0)ILI9341_DispVariable_EN(LINE(i+2), "EXC_C:", (uint16_t)EXCEPTION_CODE);
                break;
            case 6:
                ILI9341_DispVariable_EN(LINE(1), "REG:", MasterRead[1]);
                if(EXCEPTION_CODE != 0)ILI9341_DispVariable_EN(LINE(2), "EXC_C:", (uint16_t)EXCEPTION_CODE);
                break;
            default:
                break;
        }

	
        OSTimeDlyHMSM(0, 0, 0, 500);
  
        ILI9341_Clear(0, 16 * 8, LCD_X_LENGTH, LCD_Y_LENGTH - 16 * 8);	/* ��������ʾȫ�� */
	}
}
