# Description

There is a nice graphic library 
[u8g2](https://github.com/olikraus/u8g2 "u8g2 Github page") which supports a nice small and low-energy OLED display based on SSD1306 driver. Unfortunately, it's written for Arduino platform. This code was created to allow using this library with STM32 and HAL library. IT was tested with STM32L432KC processor but because of HAL it should work well on other STM32 processors.

Fortunately the [u8g2](https://github.com/olikraus/u8g2 "u8g2 Github page") library, it's designed in a way that allows for quite easy porting to other platforms, which is nicely described on the page [Porting to new MCU platform](https://github.com/olikraus/u8g2/wiki/Porting-to-new-MCU-platform "Porting to new MCU platform").

![Nucelo board photo](docs/img/board_photo.jpg?raw=true "Working SSD1306 with STM32L432")

## What was implemented
Three functions were implemented:
* `stm32_u8g2_port_module_init` - which is used to set I2C device which should be used during communication with SSD1306 display.
* `stm32_u8g2_port_delay_cblk_impl` - which is callback function used by u8g2 library for delaying,
* `stm32_u8x8_port_i2c_byte_send_cblk_impl` - which is callback used bu u8g2 for I2C communication.

# How to install stuff

1. Get the u8g2 library [from github](https://github.com/olikraus/u8g2 "u8g2 Github page").
2. Create STM32 project (the easiest way is to use CubeIDE, where I2C must be enabled and speed can be set to Fast Mode).
3. In the project create an additional directory, let's say `libraries`.
4. Copy `u8g2/csrc` directory to `libraries`.
5. Include `u8g2.h` header.
6. Add code listed below.

# How to use it

Below there is a short code snippet that shows how to use this library:
```
  // Initialize u8g2_stm_port_module
  stm32_u8g2_port_module_init(&hi2c1);

  // Initialize display.
  u8g2_t u8g2;
  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, stm32_u8x8_port_i2c_byte_send_cblk_impl, stm32_u8g2_port_delay_cblk_impl);
  u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
  u8g2_SetPowerSave(&u8g2, 0); // wake up display
  u8g2_ClearDisplay(&u8g2);

  u8g2_FirstPage(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_6x10_mf);
  u8g2_DrawStr(&u8g2, 0, 20, "u8g2 on to STM32 HAL!");
  u8g2_NextPage(&u8g2);
```

It may be pasted in the main function just after peripheral initialization.
The example can be found in an example directory.

# Additional notes

* The I2C can be set to Fast Mode (400 kHz) which improves the refresh rate.
* If other than STM32L4 processor will be used, please change the include in file `u8g2_stm32_port.h` to one corresponding to your processor.
