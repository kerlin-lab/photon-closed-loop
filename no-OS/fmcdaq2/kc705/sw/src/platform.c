/******************************************************************************
*
* Copyright (C) 2010 - 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

#define EXTERN
#include "platform.h"
#include <math.h>
#include <stdlib.h>
#define FRAME_ID 0 //use timer 0 for 0.05 ms timer (for frames)
#define CMD_ID 1 //use tmer 1 for 1 micro sec timer (for sending modulation commands)

int16_t averaged_samples[NO_COLS];
int16_t commands[NO_COLS];
//int8_t commands[NO_LINES][NO_COLS];

/*
 * Uncomment one of the following two lines, depending on the target,
 * if ps7/psu init source files are added in the source directory for
 * compiling example outside of SDK.
 */
/*#include "ps7_init.h"*/
/*#include "psu_init.h"*/

u32 current_status, prev_status=0;
u16 frame=1;
u8 send_op=0;
u16 line_no=0;
int us_count=0;
sent=0;
#ifdef STDOUT_IS_16550
 #include "xuartns550_l.h"

 #define UART_BAUD 9600
#endif

void
enable_caches()
{
#ifdef __PPC__
    Xil_ICacheEnableRegion(CACHEABLE_REGION_MASK);
    Xil_DCacheEnableRegion(CACHEABLE_REGION_MASK);
#elif __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_ICACHE
    Xil_ICacheEnable();
#endif
#ifdef XPAR_MICROBLAZE_USE_DCACHE
    Xil_DCacheEnable();
#endif
#endif
}

void
disable_caches()
{
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
    Xil_DCacheDisable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
    Xil_ICacheDisable();
#endif
#endif
}

void
init_uart()
{
#ifdef STDOUT_IS_16550
    XUartNs550_SetBaud(STDOUT_BASEADDR, XPAR_XUARTNS550_CLOCK_HZ, UART_BAUD);
    XUartNs550_SetLineControlReg(STDOUT_BASEADDR, XUN_LCR_8_DATA_BITS);
#endif
    /* Bootrom/BSP configures PS7/PSU UART to 115200 bps */
}

void platform_end() {
	int Status=XIntc_Start(&interruptCtrl, XIN_REAL_MODE);
	if(Status != XST_SUCCESS) {

		return XST_FAILURE;
	}
	/*
	* Initialize the exception table.
	*/

		Xil_ExceptionInit();

	/*
	* Register the interrupt controller handler with the exception table.
	*/
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler) XIntc_InterruptHandler, &interruptCtrl);

	/* Enable non-critical exceptions */
	Xil_ExceptionEnable();


}

void
init_platform()
{
    /*
     * If you want to run this example outside of SDK,
     * uncomment one of the following two lines and also #include "ps7_init.h"
     * or #include "ps7_init.h" at the top, depending on the target.
     * Make sure that the ps7/psu_init.c and ps7/psu_init.h files are included
     * along with this example source files for compilation.
     */
    /* ps7_init();*/
    /* psu_init();*/
	cleanup_platform();
    enable_caches();
    init_uart();
    microblaze_enable_exceptions();
    microblaze_enable_interrupts();


    platform_setup_interrupt_start();
    //int status=init_timer((XTmrCtr_Handler)sys_timer_handler);
    //if(status!=XST_SUCCESS)
    	//xil_printf("timer init failed\n");

    init_gpio(sys_trigger_handler);
    UartLiteIntr_init();

    platform_end();


}

void platform_setup_interrupt_start()
{
	// Setting up the interrupt controller
	XIntc *intcp;
	intcp = &interruptCtrl;

	XIntc_Initialize(&interruptCtrl, XPAR_INTC_0_DEVICE_ID);

}

void
cleanup_platform()
{
	microblaze_disable_exceptions();
    microblaze_disable_interrupts();
    disable_caches();
}



void sys_trigger_handler(void *CallbackRef)
{

	int16_t avg=0, test;
	int32_t sendDat;
	int16_t data,mask;

	u8 lsb, msb;

	current_status= XGpio_DiscreteRead(&gpio, 1);
	current_status=(current_status>>15) & 0x00000001;
			//xil_printf("%d\n", current_status);
	if(current_status==1 && prev_status==0) {//start of new line


		line_no++;

		if(line_no>NO_LINES) {

			line_no=1;
			frame= (frame+1) % 10;

				//GpioDisableIntr(&interruptCtrl, &gpio, GPIO_INTERRUPT_ID);
				/*for (int counter = 0; counter < FRAME_SIZE; counter++) {


									data= Xil_In16(BRAM_BASE_ADDR +counter*2);

									mask=data & 0x8000;

									if(mask)
										mask=0xc000;
									data= (data>>2) | mask;




			}*/



		}

		if(frame==1) { //output 0 + collect ADC samples every 10th frame
			XGpio_DiscreteClear(&gpio, OUTPUT_CHANNEL, OUTPUT_SMA_GPIO);
			int n=capture_ADC();
			if(!n) {
				printf("error with ADC capture\n");
			}
			else {
				//TODO call process adc data function or do something else

				for(int i=1; i<=NO_SAMPLES; i++) {
					data= Xil_In16(ADC_DDR_BASEADDR +(i-1)*2);
					mask=data & 0x8000;
										//msbyte= (data >> 8)&0xff;
					if(mask)
						mask=0xc000;
					data= (data>>2) | mask;
#ifdef SEND_SAMPLES
					XUartLite_Send(&uartInst, &data, 2);
#endif
					avg=avg+data;

					if((i%100)==0) {
						avg=avg/100;

						//averaged_samples[(i/100)-1]=avg;
						//printf("%d",avg);
#ifdef SEND_AVG
						XUartLite_Send(&uartInst, &avg, 2);
						//writeReg(avg, 'a', (line_no-1)*((i/100)-1));

						putBuff(avg);
							//XUartLite_Send(&uartInst, sendBuffer, BUFSIZE);
						sent=1;


#endif


						//command found here based on threshold
						if(abs(avg)>=THRESHOLD) {
							commands[(i/100)-1]=0;
							test=16384;
							XUartLite_Send(&uartInst, &test, 2);
							putBuff(test);



						}
						else {
							commands[(i/100)-1]=1;
							test=16383;

							XUartLite_Send(&uartInst, &test, 2);
							putBuff(test);

							//XGpio_DiscreteSet(&gpio, OUTPUT_CHANNEL, OUTPUT_SMA_GPIO);
						}
						avg=0;

					}
				}

			}
			//frame=0;
		}



	}
	prev_status=current_status;
}


void sys_timer_handler(void *CallBackRef, u8 timerID)
{
	//update this
	if(timerID==CMD_ID) {



		}


}


