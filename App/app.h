#ifndef __APP_H__
#define __APP_H__

/**************ȫ�ֱ�������************/
extern volatile uint32_t time; //�ַ�ʱ�����
extern uint8_t RX_BUFF[2048];//���ջ�����
extern uint16_t MasterRead[1000];//���յ�������
extern uint8_t EXCEPTION_CODE;

/**************�û���������************/
void Task_Start(void *p_arg);
void Task_Send(void *p_arg);
void Task_Receive(void *p_arg);
void Task_Analysis(void *p_arg);
void Task_Disp(void *p_arg);
void Task_Touch(void *p_arg);

#endif	//_APP_H_

