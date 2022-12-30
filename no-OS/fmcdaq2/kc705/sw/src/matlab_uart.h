/*
 * matlab.h
 *
 *  Created on: Apr 30, 2022
 *      Author: Kerlinlab02
 */

#ifndef MATLAB_UART_H_
#define MATLAB_UART_H_S

#include "platform_config.h"
#include "xil_printf.h"
#include "xuartlite_l.h"
#include "platform.h"

#define UART_DEVICE_ID XPAR_UARTLITE_0_DEVICE_ID
#define UARTLITE_INT_IRQ_ID XPAR_INTC_0_UARTLITE_0_VEC_ID
#define UARTLITE_ADDRESS XPAR_AXI_UART_BASEADDR
#define BUFSIZE 245
#define BUFFER_NO_BYTES TEST_BUFFER_SIZE*2

u8 recvBuffer[BUFSIZE];
extern int16_t sendBuffer[BUFSIZE];





//static volatile unsigned int TotalSentCount;
extern int line_no_sent;
int UartLiteIntr_init();

int SetupInterruptSystem(XUartLite *UartLitePtr, XIntc *intcPtr);
void RecvHandler(void *CallBackRef, unsigned int EventData);
void sendHandler(void *CallBackRef, unsigned int EventData);
int buffIsNotEmpty(void);

#endif /* MATLAB_UART_H_ */
