#ifndef __PLATFORM_CONFIG_H_
#define __PLATFORM_CONFIG_H_

#include "xtmrctr.h"
#include "xintc.h"
#include "xgpio.h"
#include "xuartlite.h"
#include "xparameters.h"
#include "xbram.h"

#ifndef EXTERN
#define EXTERN extern
#endif


#define NO_LINES 64
#define NO_COLS 245
#define FRAME_SIZE (NO_LINES*NO_COLS)
#define ADC_DDR_BASEADDR XPAR_AXI_DDR_CNTRL_BASEADDR + 0x800000
#define NO_SAMPLES (NO_COLS*100)
#define THRESHOLD 10

//uncomment if needed
#define SEND_AVG 1
//#define SEND_SAMPLES 1
//#define DEBUG_MODE //print out log

EXTERN XTmrCtr sysTmr;
EXTERN XIntc interruptCtrl;
EXTERN XGpio gpio;
EXTERN XUartLite uartInst;
EXTERN XBram bramCtrl;

EXTERN int sent;

#endif
