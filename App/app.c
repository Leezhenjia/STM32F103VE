/***************************************************************************
    ��Ȩ���У�lizhenjia
    �汾�ţ� 1.00 
    �ļ����� app.c 
    �������ڣ�2019.3.15 
    ���ߣ� lizhenjia 
    ����˵����uCOS II ����
    �����������ļ��Ĺ�ϵ�� �����ļ�
    ����˵������
    �޸ļ�¼��
            2019-03-19 lizhenjia
            ���Ӵ�����ѡ�����빦��
***************************************************************************/

#include "includes.h"

//�����������ջ
//TODO: ջ��С�����޸�
OS_STK send_task_stk[SEND_TASK_STK_SIZE]; 
OS_STK receive_task_stk[RECEIVE_TASK_STK_SIZE]; 
OS_STK analysis_task_stk[ANALYSIS_TASK_STK_SIZE]; 
OS_STK disp_task_stk[DISP_TASK_STK_SIZE]; 
OS_STK touch_task_stk[TOUCH_TASK_STK_SIZE];
 
//����,��USART�յ����ݷ��͵�Receive����
OS_EVENT *Usart_Send_Mbox;  
//����,��ʱ��7֪ͨAnalysis����ʼ��������
OS_EVENT *Tim7_Analysis_Mbox;  


uint16_t RX_CNT = 0;    //�����ֽڼ���


void Task_Start(void *p_arg)
{
	(void)p_arg;	//��ܱ���������
    
    Usart_Send_Mbox = OSMboxCreate((void *)0);
    Tim7_Analysis_Mbox = OSMboxCreate((void *)0);
    
#if OS_STK_GROWTH == 1
    OSTaskCreate(Task_Send, (void *)0, &send_task_stk[SEND_TASK_STK_SIZE - 1], SEND_TASK_PRIO);
    OSTaskCreate(Task_Receive, (void *)0, &receive_task_stk[RECEIVE_TASK_STK_SIZE - 1], RECEIVE_TASK_PRIO);
    OSTaskCreate(Task_Analysis, (void *)0, &analysis_task_stk[ANALYSIS_TASK_STK_SIZE - 1], ANALYSIS_TASK_PRIO);
    OSTaskCreate(Task_Disp, (void *)0, &disp_task_stk[DISP_TASK_STK_SIZE - 1], DISP_TASK_PRIO);
    OSTaskCreate(Task_Touch, (void *)0, &touch_task_stk[TOUCH_TASK_STK_SIZE - 1], TOUCH_TASK_PRIO);
#else
    OSTaskCreate(Task_Send, (void *)0, &send_task_stk[0], SEND_TASK_PRIO);
    OSTaskCreate(Task_Receive, (void *)0, &receive_task_stk[0], RECEIVE_TASK_PRIO);
    OSTaskCreate(Task_Analysis, (void *)0, &analysis_task_stk[0], ANALYSIS_TASK_PRIO);
    OSTaskCreate(Task_Disp, (void *)0, &disp_task_stk[0], DISP_TASK_PRIO);
    OSTaskCreate(Task_Touch, (void *)0, &touch_task_stk[0], TOUCH_TASK_PRIO);
#endif
    
	OSTaskDel(OS_PRIO_SELF);   //ɾ����ʼ����
}

void Task_Send(void *p_arg)
{
	(void)p_arg;	//��ܱ���������
	
	while (1)
	{
        if (page != 0)
        {
            ModbusRTU();    //��ʼ����ָ��
        }
		OSTimeDlyHMSM(0, 0, 2, 0);  //����2s�ȴ����ս�������
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
	(void)p_arg;	//��ܱ���������
	
    
	while (1)
	{
        Display();
        OSTimeDlyHMSM(0, 0, 0, 900);
	}
}
void Task_Touch(void *p_arg)
{
    (void)p_arg;    //��ܱ���������
    
    
    while (1)
    {
        //������⺯��������������10ms����һ��
        buttonRenew();
        XPT2046_TouchEvenHandler();
    }
}
