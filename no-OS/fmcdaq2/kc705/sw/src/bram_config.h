/*
 * bram_config.h
 *
 *  Created on: Jun 10, 2022
 *      Author: Kerlinlab02
 */

#ifndef SRC_BRAM_CONFIG_H_
#define SRC_BRAM_CONFIG_H_

#include "xbram.h"
#include "platform_config.h"

#define BRAM_DEVICE_ID XPAR_LMB_BRAM_IF_CNTLR_0_DEVICE_ID
#define BRAM_BASE_ADDR XPAR_LMB_BRAM_IF_CNTLR_0_S_AXI_CTRL_BASEADDR
#define BRAM_AVG_MATRIX_HIGH_ADDR BRAM_BASE_ADDR + FRAME_SIZE*2 //approx 31 KB used for storing averages in 64*245 frame
#define BRAM_COMMANDS_BUFF_BASE_ADDR BRAM_AVG_MATRIX_HIGH_ADDR+2
#define UART_BUFFER_START_ADDR BRAM_COMMANDS_BUFF_BASE_ADDR+2

int bram_init(void);
int BramExample(u16 DeviceId);
void InitializeECC(XBram_Config *ConfigPtr, u32 EffectiveAddr);
void writeReg(int data, char type, int index);

#endif /* SRC_BRAM_CONFIG_H_ */
