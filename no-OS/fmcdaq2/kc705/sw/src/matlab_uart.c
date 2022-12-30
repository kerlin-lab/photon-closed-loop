/*
 * matlab_uart.c
 *
 *  Created on: Apr 30, 2022
 *      Author: Kerlinlab02
 */
#include "matlab_uart.h"


int TotalReceivedCount=0;
static volatile unsigned int TotalSentCount=0;
int16_t sendBuffer[BUFSIZE];
int head=0, tail=0, prev_head=0;
u8 Index;


void RecvHandler(void *CallBackRef, unsigned int EventData)
{
	TotalReceivedCount = EventData;
	//sendBuffer[sent++]= recvBuffer[TotalReceivedCount-1];
}

void SendHandler(void *CallBackRef, unsigned int EventData)
{

	TotalSentCount = EventData;
	//head=(head+1)%BUFSIZE;

}
void sendFlag() {
	sent=1;
}
void putBuff(int16_t element) {
	sendBuffer[head]=element;
	tail=(tail+1)%BUFSIZE;
}

int getBuff(void) {
	if(head==0)
		return NULL;
		head=head-1;
	return sendBuffer[head];


}

int send_dat() {
	//XUartLite_Send(&uartInst, averaged_samples, NO_COLS*2);
	//while( TotalSentCount!= NO_COLS*2);

}

int buffIsNotEmpty(void) {
	if(head==0)
		return 0;
	else
		return 1;
}
int UartLiteIntr_init(void)
{
	int Status;


	/*
	 * Initialize the UartLite driver so that it's ready to use.
	 */
	Status = XUartLite_Initialize(&uartInst, UART_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("Uartlite_intialize failed\n");
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XUartLite_SelfTest(&uartInst);
	if (Status != XST_SUCCESS) {
		xil_printf("Uartlite self test failed\n");
		return XST_FAILURE;
	}


	Status= SetupInterruptSystem(&uartInst, &interruptCtrl);
	if(Status!=XST_SUCCESS) {
		xil_printf("Uart interrupt setup failed!\n");
		return XST_FAILURE;
	}


	/*
	* Setup the handlers for the UartLite that will be called from the
	* interrupt context when data has been sent and received, specify a
	* pointer to the UartLite driver instance as the callback reference so
	* that the handlers are able to access the instance data.
	*/
	XUartLite_SetSendHandler(&uartInst, SendHandler, &uartInst);
	//XUartLite_SetRecvHandler(&uartInst, RecvHandler, &uartInst);


	/*
	* Enable the interrupt of the UartLite so that interrupts will occur.
	*/
	XUartLite_EnableInterrupt(&uartInst);


	/*
	 * Initialize the send buffer bytes with a pattern to send and the
	* the receive buffer bytes to zero to allow the receive data to be
	* verified.
	*/
	sent=0;

	/*
	* Send the buffer using the UartLite.
	*/
	//XUartLite_Send(&uartInst, sendBuffer, BUFSIZE);

	/*
	* Start receiving data before sending it since there is a loopback.
	*/
	//int rev=XUartLite_Recv(&uartInst, recvBuffer, TEST_BUFFER_SIZE);



	/*
	* Wait for the entire buffer to be received, letting the interrupt
	* processing work in the background, this function may get locked
	* up in this loop if the interrupts are not working correctly.
	*/
	/*while ((TotalReceivedCount != TEST_BUFFER_SIZE) ||
		(TotalSentCount != TEST_BUFFER_SIZE)) {
	}*/

	/*
	* Verify the entire receive buffer was successfully received.
	*/
	/*for (Index = 0; Index < TEST_BUFFER_SIZE; Index++) {
		if (ReceiveBuffer[Index] != SendBuffer[Index]) {
			return XST_FAILURE;
		}
	}*/

//xil_xil_printf("done uart sending data\n");
		//UartLiteDisableIntrSystem(&interruptCtrl, UARTLITE_INT_IRQ_ID);

		//return XST_SUCCESS;


}

int SetupInterruptSystem(XUartLite *UartLitePtr, XIntc *intcPtr)
{

	int Status;


	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */


	/*
	 * Connect a device driver handler that will be called when an interrupt
	 * for the device occurs, the device driver handler performs the
	 * specific interrupt processing for the device.
	 */
	Status = XIntc_Connect(&interruptCtrl, UARTLITE_INT_IRQ_ID, (XInterruptHandler)XUartLite_InterruptHandler,(void *)UartLitePtr);
	if (Status != XST_SUCCESS) {
		xil_printf("Intc connect failed\n");
		return XST_FAILURE;
	}

	/*
	 * Start the interrupt controller such that interrupts are enabled for
	 * all devices that cause interrupts, specific real mode so that
	 * the UartLite can cause interrupts through the interrupt controller.
	 */
	/*Status = XIntc_Start(&interruptCtrl, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		xil_printf("failed to start uart intc!\n");
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupt for the UartLite device.
	 */
	XIntc_Enable(intcPtr, UARTLITE_INT_IRQ_ID);

	/*
	 * Initialize the exception table.
	 */
	//Xil_ExceptionInit();

	/*
	 * Register the interrupt controller handler with the exception table.
	 */
	//Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler,&interruptCtrl);

	/*
	 * Enable exceptions.
	 */
	//Xil_ExceptionEnable();

	return XST_SUCCESS;
}

void UartLiteDisableIntrSystem(XIntc *IntcInstancePtr,
					  u16 UartLiteIntrId)
{

	/*
	 * Disconnect and disable the interrupt for the UartLite.
	 */
#ifdef XPAR_INTC_0_DEVICE_ID
	XIntc_Disconnect(IntcInstancePtr, UartLiteIntrId);
#else
	XScuGic_Disable(IntcInstancePtr, UartLiteIntrId);
	XScuGic_Disconnect(IntcInstancePtr, UartLiteIntrId);

#endif

}
