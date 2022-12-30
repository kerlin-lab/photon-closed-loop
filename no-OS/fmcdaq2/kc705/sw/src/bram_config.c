/*
 * bram_config.c
 *
 *  Created on: Jun 2, 2022
 *      Author: elif cetin
 *
 */

#include "bram_config.h"

int bram_init(void)
{
	int Status;

	Status = BramExample(BRAM_DEVICE_ID);
	if (Status != XST_SUCCESS ) {
		xil_printf("Bram Interrupt Example Failed\r\n");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran Bram Interrupt Example\r\n");
	return XST_SUCCESS;
}

int BramExample(u16 DeviceId)
{
	int Status;


	/*
	 * Lookup configuration data in the device configuration table.
	 * Use this configuration info down below when initializing this
	 * driver.
	 */
	XBram_Config *ConfigPtr;
	ConfigPtr = XBram_LookupConfig(DeviceId);
	if (ConfigPtr == (XBram_Config *) NULL) {
		return XST_FAILURE;
	}

	Status = XBram_CfgInitialize(&bramCtrl, ConfigPtr,ConfigPtr->CtrlBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


    InitializeECC(ConfigPtr, ConfigPtr->CtrlBaseAddress);


	/*
	 * Execute BRAM driver selftest.
	 */
	Status = XBram_SelfTest(&bramCtrl, 0);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

void InitializeECC(XBram_Config *ConfigPtr, u32 EffectiveAddr)
{
	u32 Addr;
	volatile u32 Data;

	if (ConfigPtr->EccPresent &&
	    ConfigPtr->EccOnOffRegister &&
	    ConfigPtr->EccOnOffResetValue == 0 &&
	    ConfigPtr->WriteAccess != 0) {
		for (Addr = ConfigPtr->MemBaseAddress;
		     Addr < ConfigPtr->MemHighAddress; Addr+=4) {
			Data = XBram_In32(Addr);
			XBram_Out32(Addr, Data);
		}
		XBram_WriteReg(EffectiveAddr, XBRAM_ECC_ON_OFF_OFFSET, 1);
	}
}

void writeReg(int data, char type, int index) {
	switch (type) {

		//avg ADC frame
		case 'a':
			//XBram_Out16(data, 0x60000000+index*2);
			Xil_Out16(data, BRAM_BASE_ADDR+index*2);
			break;
		//commands frame
		case 'c':
			XBram_Out8(data, BRAM_COMMANDS_BUFF_BASE_ADDR+index);
			break;
		//uart buffer
		case 'u':
			XBram_Out16(data, UART_BUFFER_START_ADDR+index*2);
			break;
		default:
			break;

	}
}

