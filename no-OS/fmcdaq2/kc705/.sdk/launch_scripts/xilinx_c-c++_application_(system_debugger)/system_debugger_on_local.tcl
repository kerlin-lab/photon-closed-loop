connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT1 210203A7E6C9A" && level==0} -index 0
fpga -file D:/2018/no-OS/fmcdaq2/kc705/hw/system_top.bit
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent JTAG-SMT1 210203A7E6C9A"} -index 0
rst -system
after 3000
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent JTAG-SMT1 210203A7E6C9A"} -index 0
dow D:/2018/no-OS/fmcdaq2/kc705/sw/Release/sw.elf
bpadd -addr &main
