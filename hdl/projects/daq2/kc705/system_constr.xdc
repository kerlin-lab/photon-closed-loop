
# daq2

set_property -dict {PACKAGE_PIN E8} [get_ports rx_ref_clk_p]
set_property -dict {PACKAGE_PIN E7} [get_ports rx_ref_clk_n]
set_property -dict {PACKAGE_PIN A8} [get_ports {rx_data_p[0]}]
set_property -dict {PACKAGE_PIN A7} [get_ports {rx_data_n[0]}]
set_property -dict {PACKAGE_PIN E4} [get_ports {rx_data_p[1]}]
set_property -dict {PACKAGE_PIN E3} [get_ports {rx_data_n[1]}]
set_property -dict {PACKAGE_PIN B6} [get_ports {rx_data_p[2]}]
set_property -dict {PACKAGE_PIN B5} [get_ports {rx_data_n[2]}]
set_property -dict {PACKAGE_PIN D6} [get_ports {rx_data_p[3]}]
set_property -dict {PACKAGE_PIN D5} [get_ports {rx_data_n[3]}]
set_property -dict {PACKAGE_PIN D26 IOSTANDARD LVDS_25} [get_ports rx_sync_p]
set_property -dict {PACKAGE_PIN C26 IOSTANDARD LVDS_25} [get_ports rx_sync_n]
set_property -dict {PACKAGE_PIN H26 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_sysref_p]
set_property -dict {PACKAGE_PIN H27 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_sysref_n]

set_property -dict {PACKAGE_PIN C8} [get_ports tx_ref_clk_p]
set_property -dict {PACKAGE_PIN C7} [get_ports tx_ref_clk_n]
set_property -dict {PACKAGE_PIN A4} [get_ports {tx_data_p[0]}]
set_property -dict {PACKAGE_PIN A3} [get_ports {tx_data_n[0]}]
set_property -dict {PACKAGE_PIN D2} [get_ports {tx_data_p[1]}]
set_property -dict {PACKAGE_PIN D1} [get_ports {tx_data_n[1]}]
set_property -dict {PACKAGE_PIN B2} [get_ports {tx_data_p[2]}]
set_property -dict {PACKAGE_PIN B1} [get_ports {tx_data_n[2]}]
set_property -dict {PACKAGE_PIN C4} [get_ports {tx_data_p[3]}]
set_property -dict {PACKAGE_PIN C3} [get_ports {tx_data_n[3]}]
set_property -dict {PACKAGE_PIN H24 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports tx_sync_p]
set_property -dict {PACKAGE_PIN H25 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports tx_sync_n]
set_property -dict {PACKAGE_PIN G28 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports tx_sysref_p]
set_property -dict {PACKAGE_PIN F28 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports tx_sysref_n]

set_property -dict {PACKAGE_PIN G29 IOSTANDARD LVCMOS25} [get_ports spi_csn_clk]
set_property -dict {PACKAGE_PIN D29 IOSTANDARD LVCMOS25} [get_ports spi_csn_dac]
set_property -dict {PACKAGE_PIN A30 IOSTANDARD LVCMOS25} [get_ports spi_csn_adc]
set_property -dict {PACKAGE_PIN F30 IOSTANDARD LVCMOS25} [get_ports spi_clk]
set_property -dict {PACKAGE_PIN B30 IOSTANDARD LVCMOS25} [get_ports spi_sdio]
set_property -dict {PACKAGE_PIN E30 IOSTANDARD LVCMOS25} [get_ports spi_dir]

set_property -dict {PACKAGE_PIN E29 IOSTANDARD LVCMOS25} [get_ports clkd_sync]
set_property -dict {PACKAGE_PIN C30 IOSTANDARD LVCMOS25} [get_ports dac_reset]
set_property -dict {PACKAGE_PIN B29 IOSTANDARD LVCMOS25} [get_ports dac_txen]
set_property -dict {PACKAGE_PIN H30 IOSTANDARD LVCMOS25} [get_ports adc_pd]

set_property -dict {PACKAGE_PIN A25 IOSTANDARD LVCMOS25} [get_ports {clkd_status[0]}]
set_property -dict {PACKAGE_PIN A26 IOSTANDARD LVCMOS25} [get_ports {clkd_status[1]}]
set_property -dict {PACKAGE_PIN C29 IOSTANDARD LVCMOS25} [get_ports dac_irq]
set_property -dict {PACKAGE_PIN G27 IOSTANDARD LVCMOS25} [get_ports adc_fda]
set_property -dict {PACKAGE_PIN F27 IOSTANDARD LVCMOS25} [get_ports adc_fdb]

set_property -dict {PACKAGE_PIN E28 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports trig_p]
set_property -dict {PACKAGE_PIN D28 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports trig_n]

# clocks

create_clock -period 2.000 -name tx_ref_clk [get_ports tx_ref_clk_p]
create_clock -period 2.000 -name rx_ref_clk [get_ports rx_ref_clk_p]
create_clock -period 4.000 -name tx_div_clk [get_pins i_system_wrapper/system_i/util_daq2_xcvr/inst/i_xch_0/i_gtxe2_channel/TXOUTCLK]
create_clock -period 4.000 -name rx_div_clk [get_pins i_system_wrapper/system_i/util_daq2_xcvr/inst/i_xch_0/i_gtxe2_channel/RXOUTCLK]


