/*
 * LM75ADP.h
 * Author: Ron Snyder
 */

#ifndef INC_LM75ADP_H_
#define INC_LM75ADP_H_

#include <stdbool.h>
#include "stm32wlxx_hal.h"

/*
 * I2C Communication
 */
#define LM75ADP_I2C_ADDR (0x48 << 1)
#define LM75ADP_I2C_TIMEOUT 100 /* 100 ms */
#define LM75ADP_I2C_RESP_LEN 2

/*
 * Register List
 */
#define LM75ADP_Reg_Conf 0x01 // Configuration register: contains a single 8-bit data byte;tosetthedeviceoperatingcondition;default=0
#define LM75ADP_Reg_Temp 0x00 // Temperature register: contains two 8-bit data bytes; tostore the measured Temp data.
#define LM75ADP_Reg_Thyst 0x02 // Hysteresis register: contains two 8-bit data bytes; tostore the hysteresis Thyst limit; default=75°C.
#define LM75ADP_Reg_Tos 0x03 // Overtemperature shutdown threshold register: contains two 8-bit data bytes; to store the overtemperature shutdown Tos limit; default=80°C.

/*
 * Configuration Register
 */
#define LM75ADP_Config_Mode 0x02 // Bit 0 - normal(0)/Shutdown Bit 1 -  OS comparator/OS Interrupt

/*
 * Result/Measurement Struct
 */
typedef struct {
    /* Temp in Celsius */
    float f_temp;
    uint16_t i_temp;
    HAL_StatusTypeDef st_tx;
    HAL_StatusTypeDef st_rx;

} LM75ADP_Data;


/*
 * Configure Temp Sensor
 */
HAL_StatusTypeDef LM75ADP_conf(I2C_HandleTypeDef* hi2c, uint32_t Timeout);

/*
 * Read Temp Sensor
 */
HAL_StatusTypeDef LM75ADP_read(I2C_HandleTypeDef* hi2c, LM75ADP_Data* result, uint32_t Timeout);

#endif /* INC_LM75ADP_H */
