/*
 * sys_timer.h
 *
 *  Created on: Apr 13, 2022
 *      Author: Kerlinlab02
 */

#ifndef SRC_SYS_TIMER_H_
#define SRC_SYS_TIMER_H_

#include "xtmrctr.h"
#include "xstatus.h"
#include "platform_config.h"

#define TMR_ADDRESS XPAR_AXI_TIMER_BASEADDR
#define TMR_DEVICE_ID XPAR_TMRCTR_0_DEVICE_ID
#define INTC_DEVICE_ID XPAR_INTC_0_DEVICE_ID
#define TMRCTR_INTERRUPT_ID XPAR_INTC_0_TMRCTR_0_VEC_ID
#define CLOCK_FREQ XPAR_AXI_TIMER_CLOCK_FREQ_HZ
#define FRAME_ID 0 //use timer 0 for 0.05 ms timer (for frames)
#define CMD_ID 1 //use tmer 1 for 1 micro sec timer (for sending modulation commands)
#define CMD_RESET_VALUE 0xfff //(u32)((1/30*1000000)*CLOCK_FREQ)
#define FRAME_RESET_VALUE (u32)((1/(20*1000))*CLOCK_FREQ)


int setup_interrupt(XIntc *instancePtr, XTmrCtr *TmrCtrInstancePtr, u16 IntrId);
void interruptHandler (void *CallBackRef, u8 TmrCtrNumber);
int TmrCtr(XIntc *IntcInstancePtr, XTmrCtr *TmrCtrInstancePtr, u16 DeviceId, XTmrCtr_Handler handler);
int init_timer(XTmrCtr_Handler handler);



#endif /* SRC_SYS_TIMER_H_ */
