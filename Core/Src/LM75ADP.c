/*
 * LM75ADP.c
 *
 */

/**
 * https://github.com/ronsnyder
 *
*/
/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 sheinz (https://github.com/sheinz)
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "LM75ADP.h"


/*
 * Configure Temp Sensor
 */
HAL_StatusTypeDef LM75ADP_conf(I2C_HandleTypeDef *hi2c, uint32_t Timeout){
	static uint8_t command[2] = {0};
	command[0] = LM75ADP_Reg_Conf;
	command[1] = LM75ADP_Config_Mode;
	uint16_t Size = sizeof(command);
	uint16_t DevAddress = LM75ADP_I2C_ADDR;

	HAL_StatusTypeDef st_tx = HAL_I2C_Master_Transmit(hi2c, DevAddress, command, Size, LM75ADP_I2C_TIMEOUT);

	return st_tx;
}

/*
 * Read Temp Sensor
 */
HAL_StatusTypeDef LM75ADP_read(I2C_HandleTypeDef *hi2c, LM75_Data *result, uint32_t Timeout){
	static uint8_t command[1] = {0};
	command[0] = LM75ADP_Reg_Temp;
	uint16_t Size = sizeof(command);
	uint16_t DevAddress = LM75ADP_I2C_ADDR;

	static uint8_t resp[LM75ADP_I2C_RESP_LEN] = {0};

	HAL_StatusTypeDef st_tx = HAL_I2C_Master_Transmit(hi2c, DevAddress, command, Size, LM75ADP_I2C_TIMEOUT);
	result->st_tx = st_tx;
	if(st_tx == HAL_OK){
		HAL_StatusTypeDef st_rx = HAL_I2C_Master_Receive(hi2c, LM75ADP_I2C_ADDR, resp, LM75ADP_I2C_RESP_LEN, LM75ADP_I2C_TIMEOUT);

		result->st_rx = st_rx;   // store status
		st_tx = st_rx;            // return last status

		if(st_rx == HAL_OK){
			result->i_temp = (resp[0] <<8) |resp[1];  // 2s compliment value
			result->f_temp = result->i_temp / 256.0; // Float value
		}
	}
	return st_tx;
}
