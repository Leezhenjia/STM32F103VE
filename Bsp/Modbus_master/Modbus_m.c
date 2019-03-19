/***************************************************************************
    版权所有：lizhenjia
    版本号： 1.00 
    文件名： Modbus_m.c 
    生成日期：2019.3.15 
    作者： lizhenjia 
    功能说明：Modbus主机发送解析
    与所属工程文件的关系： 通信处理文件
    其它说明：暂支持03,06功能码
    修改记录：
***************************************************************************/
#include "Modbus_m.h"
#include "bsp_usart.h"
#include "CRC.h"
#include "bsp_Led.h"


uint8_t TX_EN = 0;//发送模式
uint8_t RX_EN = 0;//接收模式
extern volatile uint32_t time;
extern uint16_t RX_CNT;
uint8_t EXCEPTION_CODE = 0;//异常码

uint8_t TX_BUFF[2048];//发送缓冲区
uint8_t RX_BUFF[2048];//接收缓冲区
uint16_t MasterRead[1000];//接收到的数据
/******************************命令区******************************/
uint8_t   SlaverAddr = 0x01;    //从机地址
uint8_t   Fuction = 0x03;      // 功能码
uint16_t  StartAddr = 0x00;    //起始地址
uint16_t  ValueOrLenth = 0x03;  //数据or长度


void ModbusRTU(void)
{
    RX_CNT = 0;//清零无法解析的数据
    //TODO:后续考虑是否选择性清零    
    EXCEPTION_CODE = 0;//异常码清零
	MasterTService(SlaverAddr, Fuction, StartAddr, ValueOrLenth);
}


/******************************发送服务******************************/
void MasterTService(uint8_t SlaveAddr, uint8_t Function, uint16_t StartAddr, uint16_t ValueOrLength)
{
	switch (Function)
	{
		case 3:
			Master_03(SlaveAddr, StartAddr, ValueOrLength);//读保持寄存器
		break;
		case 6:
			Master_06(SlaveAddr, StartAddr, ValueOrLength);//写单个输出寄存器
		break;
		default:
			break;
	}
}

void Master_03(uint8_t board_addr, uint16_t start_addr, uint16_t length)
{
	uint16_t calCRC = 0;
	
	
	TX_BUFF[0] = board_addr;//地址域
	TX_BUFF[1] = 3;//功能码
	TX_BUFF[2] = HI(start_addr);
	TX_BUFF[3] = LO(start_addr);
	TX_BUFF[4] = HI(length);
	TX_BUFF[5] = LO(length);
	calCRC = CRCCompute(TX_BUFF, 6);
	TX_BUFF[6] = LO(calCRC);//低位在前
	TX_BUFF[7] = HI(calCRC);
	Usart_SendArray(USART1, TX_BUFF, 8);
}

	
void Master_06(uint8_t board_addr, uint16_t start_addr, uint16_t value)
{
	uint16_t calCRC = 0;
	
	
	TX_BUFF[0] = board_addr;//地址域
	TX_BUFF[1] = 6;//功能码
	TX_BUFF[2] = HI(start_addr);
	TX_BUFF[3] = LO(start_addr);
	TX_BUFF[4] = HI(value);
	TX_BUFF[5] = LO(value);
	calCRC = CRCCompute(TX_BUFF, 6);
	TX_BUFF[6] = LO(calCRC);//低位在前
	TX_BUFF[7] = HI(calCRC);
	Usart_SendArray(USART1, TX_BUFF, 8);
}
	
/******************************解析服务******************************/
	
void MasterAnalyService()//解析接收到的数据
{
	if (RX_BUFF[0] == SlaverAddr)
	{
		switch (RX_BUFF[1])
		{
			case 0x03:
				MasterAnaly03();
				break;
			case 6:
				MasterAnaly06();
				break;
			case 83:
				EXCEPTION_CODE = 83;//异常码0x83
				break;
			case 86:
				EXCEPTION_CODE = 86;//异常码0x86
				break;
				default:
				EXCEPTION_CODE = 1;//异常码0x01
				break;
		}
	}
	else EXCEPTION_CODE = 2;//异常码0x02
}
void MasterAnaly03(void)
{
	uint16_t calCRC = 0;
	uint16_t rxCRC = 0;
	uint8_t i = 0;
	
	
	if ((RX_CNT - 3) / 2 >= 1 && (RX_CNT - 3) / 2 <= 125)
	{
		calCRC = CRCCompute(RX_BUFF, RX_CNT - 2);
		rxCRC = RX_BUFF[RX_CNT - 2] | (((uint16_t)RX_BUFF[RX_CNT - 1]) << 8);//接收到的CRC数据低字节在前,高字节在后
		if (calCRC == rxCRC)
		{
			for (i=0; i < (RX_BUFF[2] / 2); i++)
			{
				MasterRead[i] = (((uint16_t)RX_BUFF[3 + i * 2]) << 8) | RX_BUFF[4 + i * 2];
			}
		}
		else 
		{
			EXCEPTION_CODE = 5;//自定义异常码,CRC校验未通过
		}
	}
	else 
	{
		EXCEPTION_CODE = 3;
	}
}

void MasterAnaly06(void)
{
	uint16_t calCRC = 0;
	uint16_t rxCRC = 0;
	uint8_t i = 0;

	
	calCRC = CRCCompute(RX_BUFF, RX_CNT - 2);
	rxCRC = RX_BUFF[RX_CNT-2] | (((uint16_t)RX_BUFF[RX_CNT - 1]) << 8);//接收到的CRC数据低字节在前,高字节在后
	if (calCRC == rxCRC)
	{
		for (i = 0; i < 2; i++)
		{
			MasterRead[i] = (((uint16_t)RX_BUFF[2 + i * 2]) << 8) | RX_BUFF[3 + i * 2];
		}
	}
	else 
	{
		EXCEPTION_CODE	= 5;//自定义异常码,CRC校验未通过
	}
}
	