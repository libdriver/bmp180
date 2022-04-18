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
 * @file      driver_bmp180_basic.c
 * @brief     driver bmp180 basic source file
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

#include "driver_bmp180_basic.h"

static bmp180_handle_t gs_handle;        /**< bmp180 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t bmp180_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_BMP180_LINK_INIT(&gs_handle, bmp180_handle_t); 
    DRIVER_BMP180_LINK_IIC_INIT(&gs_handle, bmp180_interface_iic_init);
    DRIVER_BMP180_LINK_IIC_DEINIT(&gs_handle, bmp180_interface_iic_deinit);
    DRIVER_BMP180_LINK_IIC_READ(&gs_handle, bmp180_interface_iic_read);
    DRIVER_BMP180_LINK_IIC_WRITE(&gs_handle, bmp180_interface_iic_write);
    DRIVER_BMP180_LINK_DELAY_MS(&gs_handle, bmp180_interface_delay_ms);
    DRIVER_BMP180_LINK_DEBUG_PRINT(&gs_handle, bmp180_interface_debug_print);
    
    /* bmp180 init */
    res = bmp180_init(&gs_handle);
    if (res != 0)
    {
        bmp180_interface_debug_print("bmp180: init failed.\n");
        
        return 1;
    }
    
    /* set mode */
    res = bmp180_set_mode(&gs_handle, BMP180_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        bmp180_interface_debug_print("bmp180: set mode failed.\n");
        (void)bmp180_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *temperature points to a converted temperature buffer
 * @param[out] *pressure points to a converted pressure buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bmp180_basic_read(float *temperature, uint32_t *pressure)
{
    uint16_t temperature_yaw;
    uint32_t pressure_yaw;
    
    /* read temperature and pressure */
    if (bmp180_read_temperature_pressure(&gs_handle, (uint16_t *)&temperature_yaw, 
                                            temperature, (uint32_t *)&pressure_yaw, pressure) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bmp180_basic_deinit(void)
{
    /* close bmp180 */
    if (bmp180_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
