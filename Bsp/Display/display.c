/***************************************************************************
    ��Ȩ���У�lizhenjia
    �汾�ţ� 1.00 
    �ļ����� display.c 
    �������ڣ�2019.3.19 
    ���ߣ� lizhenjia 
    ����˵������ʾ����Ӧ��
    �����������ļ��Ĺ�ϵ�� ��ʾӦ���ļ�
    ����˵����
    �޸ļ�¼��
***************************************************************************/
#include "includes.h"


void Display(void)
{
    LCD_SetFont(&Font16x24);
    LCD_SetColors(RED, BLACK);
    ILI9341_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH);	/* ��������ʾȫ�� */
    switch (page)
    {
        case 0:
            DisplayPage0();
            break;
        case 1:
            DisplayPage1();
        break;
        case 2:
            DisplayPage2();
        break;
        default:
            ILI9341_DispStringLine_EN(LINE(0), " Page is wrong ");//������ʾ��һ��
            break;
    }   
}
void DisplayPage0(void)
{
    ILI9341_DispStringLine_EN(LINE(0), "  MODBUS HOME  ");//������ʾ��һ��
    ILI9341_DispVariable_EN(LINE(1), "Ad: +  -   ", SlaverAddr);
    ILI9341_DispStringLine_EN(LINE(2), "03  <-Select");
    ILI9341_DispStringLine_EN(LINE(3), "06  <-Select");
}
void DisplayPage1(void)
{
    uint8_t i;
    
    
    ILI9341_DispStringLine_EN(LINE(0), "   MODBUS 03   ");//������ʾ��һ��
    ILI9341_DispVariable_EN(LINE(1), "AD  +  -   ", StartAddr);
    ILI9341_DispVariable_EN(LINE(2), "Num +  -   ", ValueOrLenth);
    ILI9341_DispStringLine_EN(LINE(12), "            ret");//����
    LCD_SetTextColor(GREEN);

    switch (RX_BUFF[1])
    {
        case 3:
            for(i = 0; i < (RX_BUFF[2] / 2); i++)
            ILI9341_DispVariable_EN(LINE(i + 3), "REG: ", MasterRead[i]);
            if(EXCEPTION_CODE != 0)ILI9341_DispVariable_EN(LINE(i + 3), "EXC_C: ", (uint16_t)EXCEPTION_CODE);
            break;
        case 6:
            ILI9341_DispVariable_EN(LINE(3), "VAL: ", MasterRead[1]);
            if(EXCEPTION_CODE != 0)ILI9341_DispVariable_EN(LINE(4), "EXC_C: ", (uint16_t)EXCEPTION_CODE);
            break;
        default:
            break;
    }
}

void DisplayPage2(void)
{
    uint8_t i;
    
    
    ILI9341_DispStringLine_EN(LINE(0), "   MODBUS 06   ");//������ʾ��һ��
    ILI9341_DispVariable_EN(LINE(1), "AD  +  -   ", StartAddr);
    ILI9341_DispVariable_EN(LINE(2), "VAL +  -   ", ValueOrLenth);
    ILI9341_DispStringLine_EN(LINE(12), "            ret");//����
    LCD_SetTextColor(GREEN);

    switch (RX_BUFF[1])
    {
        case 3:
            for(i = 0; i < (RX_BUFF[2] / 2); i++)
            ILI9341_DispVariable_EN(LINE(i + 3), "REG: ", MasterRead[i]);
            if(EXCEPTION_CODE != 0)ILI9341_DispVariable_EN(LINE(i + 3), "EXC_C: ", (uint16_t)EXCEPTION_CODE);
            break;
        case 6:
            ILI9341_DispVariable_EN(LINE(3), "VAL: ", MasterRead[1]);
            if(EXCEPTION_CODE != 0)ILI9341_DispVariable_EN(LINE(4), "EXC_C: ", (uint16_t)EXCEPTION_CODE);
            break;
        default:
            break;
    }
}


/**
  * @brief  ��ʾ����
  * @param  Line: Ҫ��ʾ����
  *   		words:��ʾ���ַ���
  * 		variable:��ʾ�ı���
  * @retval None
  */
void ILI9341_DispVariable_EN(uint16_t line, char * words, uint16_t variable	)
{
	char dispBuff[100];
	LCD_SetFont(&Font16x24);
	LCD_SetTextColor(GREEN);

	/*ʹ��c��׼��ѱ���ת�����ַ���*/
	sprintf(dispBuff,"%s%d ",words ,variable);
	LCD_ClearLine(line);	/* ����������� */
	
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	ILI9341_DispStringLine_EN(line,dispBuff);
}
