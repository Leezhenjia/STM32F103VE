/***************************************************************************
    版权所有：lizhenjia
    版本号： 1.00 
    文件名： display.c 
    生成日期：2019.3.19 
    作者： lizhenjia 
    功能说明：显示具体应用
    与所属工程文件的关系： 显示应用文件
    其它说明：
    修改记录：
***************************************************************************/
#include "includes.h"


void Display(void)
{
    LCD_SetFont(&Font16x24);
    LCD_SetColors(RED, BLACK);
    ILI9341_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH);	/* 清屏，显示全黑 */
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
            ILI9341_DispStringLine_EN(LINE(0), " Page is wrong ");//居中显示第一行
            break;
    }   
}
void DisplayPage0(void)
{
    ILI9341_DispStringLine_EN(LINE(0), "  MODBUS HOME  ");//居中显示第一行
    ILI9341_DispVariable_EN(LINE(1), "Ad: +  -   ", SlaverAddr);
    ILI9341_DispStringLine_EN(LINE(2), "03  <-Select");
    ILI9341_DispStringLine_EN(LINE(3), "06  <-Select");
}
void DisplayPage1(void)
{
    uint8_t i;
    
    
    ILI9341_DispStringLine_EN(LINE(0), "   MODBUS 03   ");//居中显示第一行
    ILI9341_DispVariable_EN(LINE(1), "AD  +  -   ", StartAddr);
    ILI9341_DispVariable_EN(LINE(2), "Num +  -   ", ValueOrLenth);
    ILI9341_DispStringLine_EN(LINE(12), "            ret");//返回
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
    
    
    ILI9341_DispStringLine_EN(LINE(0), "   MODBUS 06   ");//居中显示第一行
    ILI9341_DispVariable_EN(LINE(1), "AD  +  -   ", StartAddr);
    ILI9341_DispVariable_EN(LINE(2), "VAL +  -   ", ValueOrLenth);
    ILI9341_DispStringLine_EN(LINE(12), "            ret");//返回
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
  * @brief  显示变量
  * @param  Line: 要显示的行
  *   		words:显示的字符串
  * 		variable:显示的变量
  * @retval None
  */
void ILI9341_DispVariable_EN(uint16_t line, char * words, uint16_t variable	)
{
	char dispBuff[100];
	LCD_SetFont(&Font16x24);
	LCD_SetTextColor(GREEN);

	/*使用c标准库把变量转化成字符串*/
	sprintf(dispBuff,"%s%d ",words ,variable);
	LCD_ClearLine(line);	/* 清除单行文字 */
	
	/*然后显示该字符串即可，其它变量也是这样处理*/
	ILI9341_DispStringLine_EN(line,dispBuff);
}
