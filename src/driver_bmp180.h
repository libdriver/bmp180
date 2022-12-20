/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_bmp180.h
 * @brief     driver bmp180 header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-02-21
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/21  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/10/17  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_BMP180_H
#define DRIVER_BMP180_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup bmp180_driver bmp180 driver function
 * @brief    bmp180 driver modules
 * @{
 */

/**
 * @addtogroup bmp180_base_driver
 * @{
 */

/**
 * @brief bmp180 mode enumeration definition
 */
typedef enum
{
    BMP180_MODE_ULTRA_LOW  = 0x00,        /**< ultra low mode */
    BMP180_MODE_STANDARD   = 0x01,        /**< standard mode */
    BMP180_MODE_HIGH       = 0x02,        /**< high mode */
    BMP180_MODE_ULTRA_HIGH = 0x03,        /**< ultra high mode */
} bmp180_mode_t;

/**
 * @brief bmp180 handle structure definition
 */
typedef struct bmp180_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
    int16_t ac1;                                                                        /**< ac1 */
    int16_t ac2;                                                                        /**< ac2 */
    int16_t ac3;                                                                        /**< ac3 */
    uint16_t ac4;                                                                       /**< ac4 */
    uint16_t ac5;                                                                       /**< ac5 */
    uint16_t ac6;                                                                       /**< ac6 */
    int16_t b1;                                                                         /**< b1 */
    int16_t b2;                                                                         /**< b2 */
    int16_t mb;                                                                         /**< mb */
    int16_t mc;                                                                         /**< mc */
    int16_t md;                                                                         /**< md */
    uint8_t oss;                                                                        /**< oss param */
} bmp180_handle_t;

/**
 * @brief bmp180 information structure definition
 */
typedef struct bmp180_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} bmp180_info_t;

/**
 * @}
 */

/**
 * @defgroup bmp180_link_driver bmp180 link driver function
 * @brief    bmp180 link driver modules
 * @ingroup  bmp180_driver
 * @{
 */

/**
 * @brief     initialize bmp180_handle_t structure
 * @param[in] HANDLE points to a bmp180 handle structure
 * @param[in] STRUCTURE is bmp180_handle_t
 * @note      none
 */
#define DRIVER_BMP180_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a bmp180 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_BMP180_LINK_IIC_INIT(HANDLE, FUC)    (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a bmp180 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_BMP180_LINK_IIC_DEINIT(HANDLE, FUC)  (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to a bmp180 handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_BMP180_LINK_IIC_READ(HANDLE, FUC)    (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to a bmp180 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_BMP180_LINK_IIC_WRITE(HANDLE, FUC)   (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a bmp180 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_BMP180_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a bmp180 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_BMP180_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup bmp180_base_driver bmp180 base driver function
 * @brief    bmp180 base driver modules
 * @ingroup  bmp180_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a bmp180 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bmp180_info(bmp180_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a bmp180 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 id is error
  *           - 5 read calibration failed
 * @note      none
 */
uint8_t bmp180_init(bmp180_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a bmp180 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmp180_deinit(bmp180_handle_t *handle);

/**
 * @brief      read the temperature and pressure data
 * @param[in]  *handle points to a bmp180 handle structure
 * @param[out] *temperature_raw points to a raw temperature buffer
 * @param[out] *temperature_c points to a converted temperature buffer
 * @param[out] *pressure_raw points to a raw pressure buffer
 * @param[out] *pressure_pa points to a converted pressure buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmp180_read_temperature_pressure(bmp180_handle_t *handle, uint16_t *temperature_raw, float *temperature_c, 
                                         uint32_t *pressure_raw, uint32_t *pressure_pa);

/**
 * @brief      read the pressure data
 * @param[in]  *handle points to a bmp180 handle structure
 * @param[out] *raw points to a raw pressure buffer
 * @param[out] *pa points to a converted pressure buffer
 * @return     status code
 *             - 0 success
 *             - 1 pressure read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmp180_read_pressure(bmp180_handle_t *handle, uint32_t *raw, uint32_t *pa);

/**
 * @brief      read the temperature data
 * @param[in]  *handle points to a bmp180 handle structure
 * @param[out] *raw points to a raw temperature buffer
 * @param[out] *c points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 temperature read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmp180_read_temperature(bmp180_handle_t *handle, uint16_t *raw, float *c);

/**
 * @brief     set the measurement mode
 * @param[in] *handle points to a bmp180 handle structure
 * @param[in] mode is the measurement mode
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmp180_set_mode(bmp180_handle_t *handle, bmp180_mode_t mode);

/**
 * @brief      get the measurement mode
 * @param[in]  *handle points to a bmp180 handle structure
 * @param[out] *mode points to a measurement mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmp180_get_mode(bmp180_handle_t *handle, bmp180_mode_t *mode);

/**
 * @}
 */

/**
 * @defgroup bmp180_extend_driver bmp180 extend driver function
 * @brief    bmp180 extend driver modules
 * @ingroup  bmp180_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a bmp180 handle structure
 * @param[in] reg is the iic register address
 * @param[in] value is the data write to the register
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmp180_set_reg(bmp180_handle_t *handle, uint8_t reg, uint8_t value);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a bmp180 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *value points to a read data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmp180_get_reg(bmp180_handle_t *handle, uint8_t reg, uint8_t *value);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
