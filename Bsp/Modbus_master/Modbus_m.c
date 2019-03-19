/***************************************************************************
    ��Ȩ���У�lizhenjia
    �汾�ţ� 1.00 
    �ļ����� Modbus_m.c 
    �������ڣ�2019.3.15 
    ���ߣ� lizhenjia 
    ����˵����Modbus�������ͽ���
    �����������ļ��Ĺ�ϵ�� ͨ�Ŵ����ļ�
    ����˵������֧��03,06������
    �޸ļ�¼��
***************************************************************************/
#include "Modbus_m.h"
#include "bsp_usart.h"
#include "CRC.h"
#include "bsp_Led.h"


uint8_t TX_EN = 0;//����ģʽ
uint8_t RX_EN = 0;//����ģʽ
extern volatile uint32_t time;
extern uint16_t RX_CNT;
uint8_t EXCEPTION_CODE = 0;//�쳣��

uint8_t TX_BUFF[2048];//���ͻ�����
uint8_t RX_BUFF[2048];//���ջ�����
uint16_t MasterRead[1000];//���յ�������
/******************************������******************************/
uint8_t   SlaverAddr = 0x01;    //�ӻ���ַ
uint8_t   Fuction = 0x03;      // ������
uint16_t  StartAddr = 0x00;    //��ʼ��ַ
uint16_t  ValueOrLenth = 0x03;  //����or����


void ModbusRTU(void)
{
    RX_CNT = 0;//�����޷�����������
    //TODO:���������Ƿ�ѡ��������    
    EXCEPTION_CODE = 0;//�쳣������
	MasterTService(SlaverAddr, Fuction, StartAddr, ValueOrLenth);
}


/******************************���ͷ���******************************/
void MasterTService(uint8_t SlaveAddr, uint8_t Function, uint16_t StartAddr, uint16_t ValueOrLength)
{
	switch (Function)
	{
		case 3:
			Master_03(SlaveAddr, StartAddr, ValueOrLength);//�����ּĴ���
		break;
		case 6:
			Master_06(SlaveAddr, StartAddr, ValueOrLength);//д��������Ĵ���
		break;
		default:
			break;
	}
}

void Master_03(uint8_t board_addr, uint16_t start_addr, uint16_t length)
{
	uint16_t calCRC = 0;
	
	
	TX_BUFF[0] = board_addr;//��ַ��
	TX_BUFF[1] = 3;//������
	TX_BUFF[2] = HI(start_addr);
	TX_BUFF[3] = LO(start_addr);
	TX_BUFF[4] = HI(length);
	TX_BUFF[5] = LO(length);
	calCRC = CRCCompute(TX_BUFF, 6);
	TX_BUFF[6] = LO(calCRC);//��λ��ǰ
	TX_BUFF[7] = HI(calCRC);
	Usart_SendArray(USART1, TX_BUFF, 8);
}

	
void Master_06(uint8_t board_addr, uint16_t start_addr, uint16_t value)
{
	uint16_t calCRC = 0;
	
	
	TX_BUFF[0] = board_addr;//��ַ��
	TX_BUFF[1] = 6;//������
	TX_BUFF[2] = HI(start_addr);
	TX_BUFF[3] = LO(start_addr);
	TX_BUFF[4] = HI(value);
	TX_BUFF[5] = LO(value);
	calCRC = CRCCompute(TX_BUFF, 6);
	TX_BUFF[6] = LO(calCRC);//��λ��ǰ
	TX_BUFF[7] = HI(calCRC);
	Usart_SendArray(USART1, TX_BUFF, 8);
}
	
/******************************��������******************************/
	
void MasterAnalyService()//�������յ�������
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
				EXCEPTION_CODE = 83;//�쳣��0x83
				break;
			case 86:
				EXCEPTION_CODE = 86;//�쳣��0x86
				break;
				default:
				EXCEPTION_CODE = 1;//�쳣��0x01
				break;
		}
	}
	else EXCEPTION_CODE = 2;//�쳣��0x02
}
void MasterAnaly03(void)
{
	uint16_t calCRC = 0;
	uint16_t rxCRC = 0;
	uint8_t i = 0;
	
	
	if ((RX_CNT - 3) / 2 >= 1 && (RX_CNT - 3) / 2 <= 125)
	{
		calCRC = CRCCompute(RX_BUFF, RX_CNT - 2);
		rxCRC = RX_BUFF[RX_CNT - 2] | (((uint16_t)RX_BUFF[RX_CNT - 1]) << 8);//���յ���CRC���ݵ��ֽ���ǰ,���ֽ��ں�
		if (calCRC == rxCRC)
		{
			for (i=0; i < (RX_BUFF[2] / 2); i++)
			{
				MasterRead[i] = (((uint16_t)RX_BUFF[3 + i * 2]) << 8) | RX_BUFF[4 + i * 2];
			}
		}
		else 
		{
			EXCEPTION_CODE = 5;//�Զ����쳣��,CRCУ��δͨ��
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
	rxCRC = RX_BUFF[RX_CNT-2] | (((uint16_t)RX_BUFF[RX_CNT - 1]) << 8);//���յ���CRC���ݵ��ֽ���ǰ,���ֽ��ں�
	if (calCRC == rxCRC)
	{
		for (i = 0; i < 2; i++)
		{
			MasterRead[i] = (((uint16_t)RX_BUFF[2 + i * 2]) << 8) | RX_BUFF[3 + i * 2];
		}
	}
	else 
	{
		EXCEPTION_CODE	= 5;//�Զ����쳣��,CRCУ��δͨ��
	}
}
	