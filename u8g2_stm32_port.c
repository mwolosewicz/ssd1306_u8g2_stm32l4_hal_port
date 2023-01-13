/*
 * u8g2_stm32_port.c
 *
 *  Created on: Jan 13, 2023
 *      Author: Maciej Wolosewicz
 */

#include <assert.h>
#include <stdio.h>
#include <u8g2_stm32_port.h>
#include <string.h>

/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
#define SEND_BUFFER_MAX_SIZE (uint8_t)(32u)

static I2C_HandleTypeDef *i2c_device;
static uint8_t tx_buff[SEND_BUFFER_MAX_SIZE];
static uint8_t tx_buff_data_pointer_pos;

static void add_data_to_tx_buff(const uint8_t *data, const uint8_t len) {
  assert(!(SEND_BUFFER_MAX_SIZE < (tx_buff_data_pointer_pos + len))); /* Check if tx_buff_data_pointer_pos will not goes out of buffer. */
  memcpy(tx_buff + tx_buff_data_pointer_pos, data, len);
  tx_buff_data_pointer_pos += len;
}

static void reset_tx_buff() {
  memset(tx_buff, 0, SEND_BUFFER_MAX_SIZE);
  tx_buff_data_pointer_pos = 0;
}

static uint8_t send_data(const uint8_t addr) {
  assert(i2c_device);
  HAL_StatusTypeDef transmission_status = HAL_I2C_Master_Transmit(i2c_device, addr, tx_buff, tx_buff_data_pointer_pos, HAL_MAX_DELAY);
  return (transmission_status != HAL_OK) ? 0 : 1;
}

/* Public API implementation */
void stm32_u8g2_port_module_init(I2C_HandleTypeDef *hi2c) {
  assert(hi2c);
  i2c_device = hi2c;
}

uint8_t stm32_u8g2_port_delay_cblk_impl(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
  /* For I2C communication only U8X8_MSG_DELAY_MILLI must be implemented. */
  if (U8X8_MSG_DELAY_MILLI == msg) {
    HAL_Delay(arg_int);
  }
  return 1;
}

uint8_t stm32_u8x8_port_i2c_byte_send_cblk_impl(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {

  uint8_t ret_val = 1;

  switch(msg) {
    case U8X8_MSG_BYTE_SEND:
      add_data_to_tx_buff(arg_ptr, arg_int);
      break;
    case U8X8_MSG_BYTE_START_TRANSFER:
      reset_tx_buff();
    break;
    case U8X8_MSG_BYTE_END_TRANSFER:
      assert(i2c_device);
      ret_val = send_data(u8x8_GetI2CAddress(u8x8));
      break;
    default:
      ret_val = 0;
  }
  return ret_val;
}


