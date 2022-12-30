/*
 * gpio.h
 *
 *  Created on: Apr 13, 2022
 *      Author: Elif Cetin
 */

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include "platform_config.h"
//#include "sys_timer.h"
#include "xgpio.h"
#include "platform.h"

# define OUTPUT_CHANNEL 1 //gpio channel with the output pin
//bit 16= SMA positive , bit 15= SMA NEGATIVE
#define OUTPUT_SMA_GPIO 0x10
#define TRIGGER_DETECT_GPIO 0x0f
#define GPIO_DEVICE_ID XPAR_GPIO_0_DEVICE_ID
#define GPIO_INTERRUPT_ID XPAR_INTC_0_GPIO_0_VEC_ID


//extern u32 current_status, prev_status, frame;
//extern u16 line_no;
//extern u8 send_op;

int init_gpio(Xil_ExceptionHandler handler);
int xgpio_initialize(XGpio *gpio_instance, XIntc *instancePtr, Xil_ExceptionHandler handler);
int setup_gpio_interrupt(XGpio *gpio_instance, XIntc *instancePtr, Xil_ExceptionHandler handler);
void GpioHandler(void *CallbackRef);
void trigger_adc_process(void);

int setHigh(XGpio *gpio_instance);
int setLow(XGpio *gpio_instance);

#endif /* SRC_GPIO_H_ */

