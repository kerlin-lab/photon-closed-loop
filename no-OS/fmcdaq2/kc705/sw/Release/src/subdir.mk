################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/ad9144.c \
../src/ad9523.c \
../src/ad9680.c \
../src/adc_core.c \
../src/altera_a10_atx_pll.c \
../src/altera_a10_fpll.c \
../src/altera_a10_xcvr_channel.c \
../src/altera_pll_common.c \
../src/bram_config.c \
../src/dac_buffer.c \
../src/dac_core.c \
../src/dmac_core.c \
../src/fmcdaq2.c \
../src/gpio.c \
../src/jesd_core.c \
../src/matlab_uart.c \
../src/platform.c \
../src/platform_drivers.c \
../src/sys_timer.c \
../src/xcvr_core.c \
../src/xilinx_qpll.c \
../src/xilinx_xcvr_channel.c 

OBJS += \
./src/ad9144.o \
./src/ad9523.o \
./src/ad9680.o \
./src/adc_core.o \
./src/altera_a10_atx_pll.o \
./src/altera_a10_fpll.o \
./src/altera_a10_xcvr_channel.o \
./src/altera_pll_common.o \
./src/bram_config.o \
./src/dac_buffer.o \
./src/dac_core.o \
./src/dmac_core.o \
./src/fmcdaq2.o \
./src/gpio.o \
./src/jesd_core.o \
./src/matlab_uart.o \
./src/platform.o \
./src/platform_drivers.o \
./src/sys_timer.o \
./src/xcvr_core.o \
./src/xilinx_qpll.o \
./src/xilinx_xcvr_channel.o 

C_DEPS += \
./src/ad9144.d \
./src/ad9523.d \
./src/ad9680.d \
./src/adc_core.d \
./src/altera_a10_atx_pll.d \
./src/altera_a10_fpll.d \
./src/altera_a10_xcvr_channel.d \
./src/altera_pll_common.d \
./src/bram_config.d \
./src/dac_buffer.d \
./src/dac_core.d \
./src/dmac_core.d \
./src/fmcdaq2.d \
./src/gpio.d \
./src/jesd_core.d \
./src/matlab_uart.d \
./src/platform.d \
./src/platform_drivers.d \
./src/sys_timer.d \
./src/xcvr_core.d \
./src/xilinx_qpll.d \
./src/xilinx_xcvr_channel.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -DXILINX -DMICROBLAZE -Wall -O2 -c -fmessage-length=0 -MT"$@" -I../../bsp/sys_mb/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mno-xl-soft-div -mcpu=v11.0 -mno-xl-soft-mul -mxl-multiply-high -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


