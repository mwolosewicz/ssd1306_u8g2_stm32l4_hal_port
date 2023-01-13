/*
 * u8g2_stm32_port.h
 *
 * @brief Interface for u8g2 library which can be used with STM32 processors using HAL library.
 *
 * Both functions: u8g2_hal_delay_callback_impl and u8x8_hal_i2c_byte_comm_callback_impl should be registered
 * using one of setup function, ex. u8g2_Setup_ssd1306_i2c_128x64_noname_f.
 *
 *  Created on: Jan 13, 2023
 *      Author: Maciej Wolosewicz
 */

#ifndef SRC_U8G2_STM32_PORT_H_
#define SRC_U8G2_STM32_PORT_H_

#include <stm32l4xx_hal.h>
#include <stdint.h>
#include <u8g2.h>

/**
 * @brief Set I2C device which should be used to handle u8g2 communication commands.
 *
 * @param p_hi2c is a pointer to i2c device.
 */
void stm32_u8g2_port_module_init(I2C_HandleTypeDef *p_hi2c);

/**
 * @brief Implementation of GPIO and Delay callback @see u8x8_msg_cb in u8g2.h file.
 */
uint8_t stm32_u8g2_port_delay_cblk_impl(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

/**
 * @brief Implementation of u8x8 byte communication callback @see u8x8_msg_cb in u8g2.h file.
 */
uint8_t stm32_u8x8_port_i2c_byte_send_cblk_impl(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


#endif /* SRC_U8G2_STM32_PORT_H_ */
