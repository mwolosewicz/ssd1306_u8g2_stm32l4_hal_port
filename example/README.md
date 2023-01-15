# How to use this example
In this directory, there is working code ready to build and flash to your uC.

## Cloning submodule
This directory contains u8g2 subrepository which must be initialized, to do so please:

1. If you do not clone this repository yet, you should use"
```
git clone --recurse-submodules git@github.com:mwolosewicz/ssd1306_u8g2_stm32l4_hal_port.git
```

2. If you have downloaded repository, but subrepo is not initialized please call this from repo directory:
```
git submodule update --init --recursive
```

## Preparing tools
For build and flash the image you will need a toolchain and st-link.

### Installing the toolchain
On Ubuntu: `sudo apt-get install gcc-arm-none-eabi gdb-arm-none-eabi`.

### Installing the st-link
The ST-Link can be found on the github at [stlink-org/stlink](https://github.com/stlink-org/stlink "stlink-org/stlink"). To install it, please follow the instructions described in the project readme.

### How to connect board with SSD1306
In the example I2C is configured to use default GPIO, so:
* SDA is PA10 (on STM32FL432KC PCB is marked as D0/RX),
* SCL is PA9 (on STM32FL432KC PCB is marked as D1/TX).

Note, that on the SSD1306 evaluation modules usually there are I2C resistors, so it may be connected directly to the board.

### Flashing the device
1. Connect board over USB.
2. Check if it's detected using `st-info --probe`. You should see something like this (don't worry about *unrecognized flash type*):
```
Failed to parse flash type or unrecognized flash type
Found 1 stlink programmers
  version:    V2J40S27
  serial:     066CFF535155878281104210
  flash:      262144 (pagesize: 2048)
  sram:       49152
  chipid:     0x435
  dev-type:   STM32L41x_L42x
```

3. Then build an example using `make -j` If everything went well you should see the following info at the end:
```
arm-none-eabi-size build/u8g2_port_example.elf
   text	   data	    bss	    dec	    hex	filename
  29416	    128	   2872	  32416	   7ea0	build/u8g2_port_example.elf
arm-none-eabi-objcopy -O ihex build/u8g2_port_example.elf build/u8g2_port_example.hex
arm-none-eabi-objcopy -O binary -S build/u8g2_port_example.elf build/u8g2_port_example.bin
```

4. And at the end, flash using `st-flash write build/u8g2_port_example.bin 0x8000000` at the end you should see the simmilar log:
```
2023-01-15T16:55:10 INFO flashloader.c: Starting Flash write for F2/F4/F7/L4
2023-01-15T16:55:10 INFO flash_loader.c: Successfully loaded flash loader in sram
2023-01-15T16:55:10 INFO flash_loader.c: Clear DFSR
2023-01-15T16:55:10 INFO common_flash.c: Starting verification of write complete
2023-01-15T16:55:10 INFO common_flash.c: Flash written and verified! jolly good!
```

This means that software is flashed and program should show text on the SSD1306 display. If display is black, please make sure that the connection between SSD1306 and Nucleo board are correct. 
