#ifndef __APP_H__
#define __APP_H__

/**************全局变量声明************/
extern volatile uint32_t time; //字符时间计数
extern uint8_t RX_BUFF[2048];//接收缓冲区
extern uint16_t MasterRead[1000];//接收到的数据
extern uint8_t EXCEPTION_CODE;

/**************用户任务声明************/
void Task_Start(void *p_arg);
void Task_Send(void *p_arg);
void Task_Receive(void *p_arg);
void Task_Analysis(void *p_arg);
void Task_Disp(void *p_arg);
void Task_Touch(void *p_arg);

#endif	//_APP_H_

