/*
 * timer.c
 *
 *  Created on: Apr 1, 2022
 *      Author: elif cetin
 */

#include "sys_timer.h"




int setup_interrupt(XIntc *instancePtr, XTmrCtr *TmrCtrInstancePtr, u16 IntrId) {
	int Status;


	//initialize XIntc instance
	/*Status= XIntc_Initialize(instancePtr, IntrId);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}*/

	//make connection between interrupt source and interrupt handler
	//XTmrCtr_InterruptHandler is declated in xtmrctr_intr.c and is the default handler
	Status = XIntc_Connect(instancePtr, IntrId, (XInterruptHandler)XTmrCtr_InterruptHandler, (void *)TmrCtrInstancePtr);
	if(Status != XST_SUCCESS) {
		printf("test 3 faiiled\n");
		return XST_FAILURE;
	}
	//Status=XIntc_Start(instancePtr, XIN_REAL_MODE);
	if(Status != XST_SUCCESS) {
			printf("start failed\n");
			return XST_FAILURE;
		}
	//enable interrupt
	XIntc_Enable(instancePtr, IntrId);

	return XST_SUCCESS;
}


//TODO interrupt handler
void interruptHandler (void *CallBackRef, u8 TmrCtrNumber) {
	//1 us timer
	printf("interrupt handler\n");
	if(TmrCtrNumber==CMD_ID) {


		//us_count++;
		//command_calc();
	}

	else if(TmrCtrNumber==FRAME_ID) {
		printf("hi\n");
		/*u32 current_status= XGpio_DiscreteRead(&gpio, 1);
		printf("whole thing read %lu\n", current_status);
		current_status=(current_status>>15) & 0x00000001;
		if(current_status)
			printf("high detected\n");*/
		//printf("%lu\n", current_status);
		//frame_count++;
		//frame_calc();
	}
}

int TmrCtr(XIntc *IntcInstancePtr, XTmrCtr *TmrCtrInstancePtr, u16 DeviceId, XTmrCtr_Handler handler) {
	int status;
	//intialize tmr driver
	status= XTmrCtr_Initialize(TmrCtrInstancePtr, TMR_DEVICE_ID);
	printf("memory read\n");
	if(status!= XST_SUCCESS) {
		printf("Timer init failed\n");
		return XST_FAILURE;
	}

	printf("tmr init passed!\n");
	/*
	 * Perform a self-test to ensure that the hardware was built
	* correctly, use the 1st timer
	*/
	status = XTmrCtr_SelfTest(TmrCtrInstancePtr, FRAME_ID);
	if (status != XST_SUCCESS) {
	printf("test faiiled\n");
	return XST_FAILURE;

	}
	//test on second timer
	status = XTmrCtr_SelfTest(TmrCtrInstancePtr, CMD_ID);
	if (status != XST_SUCCESS) {
		printf("test 2 faiiled\n");
		return XST_FAILURE;
	}
	printf("self test passed\n");
	//setup interrupt
	status=setup_interrupt(IntcInstancePtr, TmrCtrInstancePtr, TMRCTR_INTERRUPT_ID);
	if (status!=XST_SUCCESS){
		printf("setup_interrupt failed!\n");
		return XST_FAILURE;
	}
	//setup interrupt handler function
	XTmrCtr_SetHandler(TmrCtrInstancePtr, handler, TmrCtrInstancePtr);

	//enable auto reload mode and interrupt mode for both counters
	//enable down count mode- reset value is written at start of program and also reloaded when counter reaches 0
	XTmrCtr_SetOptions(TmrCtrInstancePtr, CMD_ID, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION | XTC_DOWN_COUNT_OPTION);
	XTmrCtr_SetOptions(TmrCtrInstancePtr, FRAME_ID, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION | XTC_DOWN_COUNT_OPTION);
	printf("set options!\n");
	//set counter reset values for both counters
	//TODO: Calculate reset values
	XTmrCtr_SetResetValue(TmrCtrInstancePtr, CMD_ID, CMD_RESET_VALUE);
	XTmrCtr_SetResetValue(TmrCtrInstancePtr, FRAME_ID, FRAME_RESET_VALUE);

	//start the timers
	XTmrCtr_Start(TmrCtrInstancePtr, CMD_ID);
	XTmrCtr_Start(TmrCtrInstancePtr, FRAME_ID);

	printf("timers started\n");
	return XST_SUCCESS;
}


int init_timer(XTmrCtr_Handler handler) {
	int Status= TmrCtr(&interruptCtrl,&sysTmr, TMR_DEVICE_ID, handler);
	if(Status!=XST_SUCCESS) {
		printf("timer init gone wrong\n");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}
