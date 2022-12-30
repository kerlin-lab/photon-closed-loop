# thesis-project

## Compiling DAQ board 

## HDL project
There are two ways to use the FMCDAQ2 board from Analog devices- using the provided Linux OS or bare-metal (no-OS) approach. This project will use the no-OS approach to have total control over timing. Compile the HDL project first before compiling the no-OS project. 
<br><br>
Note: The files in this repo and the following instructions are made to work with Vivado 2019.1. Check Analog Devices' repository for different versions, or try following these instructions and change rules in scripts based on error messages. (former option is much easier) 
1. Install cygwin 
2. Change the PATH system variable to the bin folder of Vivado. ex: <br> `PATH=$PATH:/cygdrive/d/xilinx/vivado/2019.1/bin` 
3. Change to directory of the project (/hdl/projects/daq2/kc705)
4. Run `make`
5. After make is complete (might take a while- be patient :) ): <br> You will find the built project under hdl/projects/daq2/kc705 
6. Open the project (it will be an .xpr file) in Vivado and ** Run Synthesis **
7. ** Generate Bitstream ** (also might take a while)
8. After bitstream is generated, click File -> Export -> Export Hardware

## no-OS Project 
Note: These instructions are for building the project on a Windows machine
1. After following the above instructions, go to the hdl/projects/daq2/kc705/daq2_kc705.sdk folder 
2. Copy the system.hdf file 
3. Go to the no-OS project folder (no-OS/projects/fmcdaq2) and paste the hdf file here 
4. Install GNU make
5. Open command prompt as admin (use command prompt for these next instructions) and set PATH environment variable to gnuwin/bin folder in Vivado SDK folder. ex: `set PATH=%PATH%;D:\Xilinx\SDK\2019.1\gnuwin\bin`
6. cd to project folder
7. Run settings64.bat from the Xilinx SDK folder. ex: `D:\Xilinx\SDK\2019.1\settings64.bat`
8. Run make


