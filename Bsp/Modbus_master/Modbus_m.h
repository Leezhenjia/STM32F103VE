#ifndef __MODBUS_H__
#define __MODBUS_H__

#include "stdint.h"

#define HI(n) ((n)>>8)
#define LO(n) ((n)&0xff)

void ModbusRTU(void);
void MasterTService(uint8_t SlaveAddr,uint8_t Function,uint16_t StartAddr,uint16_t ValueOrLength);

void Master_03(uint8_t board_addr,uint16_t start_addr,uint16_t length);
void Master_06(uint8_t board_addr,uint16_t start_addr,uint16_t value);

void MasterAnalyService(void);

void MasterAnaly03(void);
void MasterAnaly06(void);


#endif /*__MODBUS_H__*/
