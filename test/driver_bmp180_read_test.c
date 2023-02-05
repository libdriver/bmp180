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
 * @file      driver_bmp180_read_test.c
 * @brief     driver bmp180 read test source file
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

#include "driver_bmp180_read_test.h"

static bmp180_handle_t gs_handle;        /**< bmp180 handle */

/**
 * @brief     read test
 * @param[in] times is the read times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bmp180_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    uint16_t temperature_yaw;
    float temperature_c;
    uint32_t pressure_yaw;
    uint32_t pressure_pa;
    bmp180_info_t info;
    
    /* link interface function */
    DRIVER_BMP180_LINK_INIT(&gs_handle, bmp180_handle_t); 
    DRIVER_BMP180_LINK_IIC_INIT(&gs_handle, bmp180_interface_iic_init);
    DRIVER_BMP180_LINK_IIC_DEINIT(&gs_handle, bmp180_interface_iic_deinit);
    DRIVER_BMP180_LINK_IIC_READ(&gs_handle, bmp180_interface_iic_read);
    DRIVER_BMP180_LINK_IIC_WRITE(&gs_handle, bmp180_interface_iic_write);
    DRIVER_BMP180_LINK_DELAY_MS(&gs_handle, bmp180_interface_delay_ms);
    DRIVER_BMP180_LINK_DEBUG_PRINT(&gs_handle, bmp180_interface_debug_print);
    
    /* get bmp180 info */
    res = bmp180_info(&info);
    if (res != 0)
    {
        bmp180_interface_debug_print("bmp180: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print bmp180 */
        bmp180_interface_debug_print("bmp180: chip is %s.\n", info.chip_name);
        bmp180_interface_debug_print("bmp180: manufacturer is %s.\n", info.manufacturer_name);
        bmp180_interface_debug_print("bmp180: interface is %s.\n", info.interface);
        bmp180_interface_debug_print("bmp180: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bmp180_interface_debug_print("bmp180: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bmp180_interface_debug_print("bmp180: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bmp180_interface_debug_print("bmp180: max current is %0.2fmA.\n", info.max_current_ma);
        bmp180_interface_debug_print("bmp180: max temperature is %0.1fC.\n", info.temperature_max);
        bmp180_interface_debug_print("bmp180: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    bmp180_interface_debug_print("bmp180: start read test.\n");
    res = bmp180_init(&gs_handle);
    if (res != 0)
    {
        bmp180_interface_debug_print("bmp180: init failed.\n");
       
        return 1;
    }
    
    /* set ultra_low mode */
    res = bmp180_set_mode(&gs_handle, BMP180_MODE_ULTRA_LOW);
    if (res != 0)
    {
        bmp180_interface_debug_print("bmp180: set ultra low mode failed.\n");
        (void)bmp180_deinit(&gs_handle); 
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        res = bmp180_read_temperature_pressure(&gs_handle, (uint16_t *)&temperature_yaw, (float *)&temperature_c, (uint32_t *)&pressure_yaw, (uint32_t *)&pressure_pa);
        if (res != 0)
        {
            bmp180_interface_debug_print("bmp180: read failed.\n");
            (void)bmp180_deinit(&gs_handle); 
            
            return 1;
        }
        bmp180_interface_debug_print("bmp180: ultra low mode temperature: %.01fC.\n", temperature_c);
        bmp180_interface_debug_print("bmp180: ultra low mode pressure: %dPa.\n", pressure_pa);
        bmp180_interface_delay_ms(1000);
    }
    
    /* set standard mode */
    res = bmp180_set_mode(&gs_handle, BMP180_MODE_STANDARD);
    if (res != 0)
    {
        bmp180_interface_debug_print("bmp180: set standard mode failed.\n");
        (void)bmp180_deinit(&gs_handle); 
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        res = bmp180_read_temperature_pressure(&gs_handle, (uint16_t *)&temperature_yaw, (float *)&temperature_c, (uint32_t *)&pressure_yaw, (uint32_t *)&pressure_pa);
        if (res != 0)
        {
            bmp180_interface_debug_print("bmp180: read failed.\n");
            (void)bmp180_deinit(&gs_handle); 
            
            return 1;
        }
        bmp180_interface_debug_print("bmp180: standard mode temperature: %.01fC.\n", temperature_c);
        bmp180_interface_debug_print("bmp180: standard mode pressure: %dPa.\n", pressure_pa);
        bmp180_interface_delay_ms(1000);
    }
    
    /* set high mode */
    res = bmp180_set_mode(&gs_handle, BMP180_MODE_HIGH);
    if (res != 0)
    {
        bmp180_interface_debug_print("bmp180: set high mode failed.\n");
        (void)bmp180_deinit(&gs_handle); 
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        res = bmp180_read_temperature_pressure(&gs_handle, (uint16_t *)&temperature_yaw, (float *)&temperature_c, (uint32_t *)&pressure_yaw, (uint32_t *)&pressure_pa);
        if (res != 0)
        {
            bmp180_interface_debug_print("bmp180: read failed.\n");
            (void)bmp180_deinit(&gs_handle); 
            
            return 1;
        }
        bmp180_interface_debug_print("bmp180: high mode temperature: %.01fC.\n", temperature_c);
        bmp180_interface_debug_print("bmp180: high mode pressure: %dPa.\n", pressure_pa);
        bmp180_interface_delay_ms(1000);
    }
    
    /* set ultra_high mode */
    res = bmp180_set_mode(&gs_handle, BMP180_MODE_ULTRA_HIGH);
    if (res != 0)
    {
        bmp180_interface_debug_print("bmp180: set ultra high mode failed.\n");
        (void)bmp180_deinit(&gs_handle); 
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        res = bmp180_read_temperature_pressure(&gs_handle, (uint16_t *)&temperature_yaw, (float *)&temperature_c, (uint32_t *)&pressure_yaw, (uint32_t *)&pressure_pa);
        if (res != 0)
        {
            bmp180_interface_debug_print("bmp180: read failed.\n");
            (void)bmp180_deinit(&gs_handle); 
            
            return 1;
        }
        bmp180_interface_debug_print("bmp180: ultra high mode temperature: %.01fC.\n", temperature_c);
        bmp180_interface_debug_print("bmp180: ultra high mode pressure: %dPa.\n", pressure_pa);
        bmp180_interface_delay_ms(1000);
    }
    
    /* finish read test */
    bmp180_interface_debug_print("bmp180: finish read test.\n");
    (void)bmp180_deinit(&gs_handle); 
    
    return 0;
}
