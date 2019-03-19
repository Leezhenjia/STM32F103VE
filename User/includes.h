#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include "stm32f10x.h"
#include "stm32f10x_it.h"   //�ж����
#include "stm32f10x_rcc.h"	//��ʱ�����

#include "ucos_ii.h"		//ucosiiϵͳ����ͷ�ļ�

#include "BSP.h"			//��������غ���
#include "app.h"			//�û�������
#include "bsp_led.h"		//led��������
#include "bsp_ili9341_lcd.h"//LCD��ʾ����������
#include "bsp_usart.h"      //usart��������
#include "Modbus_m.h"       //MODBUS��Լ����
#include "CRC.h"            //CRC������麯��
#include "bsp_tim.h"     //��ʱ������
#include "bsp_spi_flash.h"  //flash����
#include "bsp_xpt2046_lcd.h"//��������������
#include "touchapp.h"        //���������洦����
#include "display.h"        //��ʾ����ʾ����

#endif //__INCLUDES_H__
