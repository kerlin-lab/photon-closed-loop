/*
 * gpio.c
 *
 *  Created on: Apr 1, 2022
 *      Author: Elif Cetin
 */

#include "gpio.h"



int setup_gpio_interrupt(XGpio *gpio_instance, XIntc *instancePtr, Xil_ExceptionHandler handler) {
	int status;

	status = XIntc_Connect(instancePtr, GPIO_INTERRUPT_ID, (Xil_ExceptionHandler) GpioHandler, handler);
	if(status!=XST_SUCCESS) {
		printf("error with gpio interrupt init\n");
		return XST_FAILURE;
	}
	XIntc_Enable(instancePtr, GPIO_INTERRUPT_ID);
	XGpio_InterruptEnable(gpio_instance,(u32)XGPIO_IR_CH1_MASK); //try using 0xff as mask
	XGpio_InterruptGlobalEnable(gpio_instance);


	return XST_SUCCESS;
}

int xgpio_initialize(XGpio *gpio_instance, XIntc *instancePtr, Xil_ExceptionHandler handler) {
    int status;
    status= XGpio_Initialize(gpio_instance, GPIO_DEVICE_ID);
    if(status!=XST_SUCCESS) {
        printf("xilinx GPIO init failed!\n");
        return XST_FAILURE;
    }

    XGpio_SetDataDirection(gpio_instance, OUTPUT_CHANNEL, 0x00c03f); //pins 15 is input and 16 is output

    //Gpio_DiscreteClear(gpio_instance, OUTPUT_CHANNEL, SMA_N); //clear the N signal
   // XGpio_DiscreteSet(&gpio, OUTPUT_CHANNEL, SMA_P);
    status=setup_gpio_interrupt(gpio_instance, instancePtr, handler);
    //XGpio_DiscreteWrite(gpio_instance, OUTPUT_CHANNEL, 0x0010000);
    return XST_SUCCESS;
}




/*
 * Gpio interrupt handler function- happens when change in signal is detected on the pin
 */
void GpioHandler(void *CallbackRef) {


		((Xil_ExceptionHandler)CallbackRef)(NULL);
		XGpio_InterruptClear(&gpio, XGPIO_IR_CH1_MASK);
}



/*void trigger_adc_process(void) {

	int16_t data;
	int32_t avg=0;
	int i=0;

	for(int count=0; count<NO_ADC_SAMPLES; count++) {
		i++;
		data= Xil_In16(ADC_DDR_ADDRESS+count*2);
		avg+=data;
		if(i==100) {
			i=0;
			ADC_averages[(count+1)/100] = avg/100; //TODO declare this data structure or find solution for storing this data
			avg=0;
		}
	}

}*/



int init_gpio(Xil_ExceptionHandler handler) {
	int status= xgpio_initialize(&gpio, &interruptCtrl, handler);

	if(status!=XST_SUCCESS) {
		printf("gpio failed\n");
	}
	return status;
}



int nextAddress(u32 address) {
	return Xil_In16(ADC_DDR_BASEADDR + address);
}

void GpioDisableIntr(XIntc *IntcInstancePtr, XGpio *InstancePtr,
			u16 IntrId)
{
	XGpio_InterruptDisable(InstancePtr, XGPIO_IR_CH1_MASK);
	XIntc_Disable(IntcInstancePtr, IntrId);
	return;
}

void GpioEnableIntr(XIntc *IntcInstancePtr, XGpio *InstancePtr, u16 IntrId) {
	XIntc_Enable(IntcInstancePtr, GPIO_INTERRUPT_ID);
	XGpio_InterruptEnable(InstancePtr,(u32)XGPIO_IR_CH1_MASK); //try using 0xff as mask
	XGpio_InterruptGlobalEnable(InstancePtr);


}
