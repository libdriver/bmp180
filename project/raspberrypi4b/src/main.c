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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-02-21
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/21  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_bmp180_read_test.h"
#include "driver_bmp180_register_test.h"
#include "driver_bmp180_basic.h"
#include <stdlib.h>

/**
 * @brief     bmp180 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t bmp180(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            bmp180_info_t info;
            
            /* print bmp180 info */
            bmp180_info(&info);
            bmp180_interface_debug_print("bmp180: chip is %s.\n", info.chip_name);
            bmp180_interface_debug_print("bmp180: manufacturer is %s.\n", info.manufacturer_name);
            bmp180_interface_debug_print("bmp180: interface is %s.\n", info.interface);
            bmp180_interface_debug_print("bmp180: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            bmp180_interface_debug_print("bmp180: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            bmp180_interface_debug_print("bmp180: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            bmp180_interface_debug_print("bmp180: max current is %0.2fmA.\n", info.max_current_ma);
            bmp180_interface_debug_print("bmp180: max temperature is %0.1fC.\n", info.temperature_max);
            bmp180_interface_debug_print("bmp180: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            bmp180_interface_debug_print("bmp180: SCL connected to GPIO3(BCM).\n");
            bmp180_interface_debug_print("bmp180: SDA connected to GPIO2(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show bmp180 help */
            
            help:
            
            bmp180_interface_debug_print("bmp180 -i\n\tshow bmp180 chip and driver information.\n");
            bmp180_interface_debug_print("bmp180 -h\n\tshow bmp180 help.\n");
            bmp180_interface_debug_print("bmp180 -p\n\tshow bmp180 pin connections of the current board.\n");
            bmp180_interface_debug_print("bmp180 -t reg\n\trun bmp180 register test.\n");
            bmp180_interface_debug_print("bmp180 -t read <times>\n\trun bmp180 read test.times means test times.\n");
            bmp180_interface_debug_print("bmp180 -c read <times>\n\trun bmp180 read function.times means read times.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                /* run reg test */
                if (bmp180_register_test())
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                /* run read test */
                if (bmp180_read_test(atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        
            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times;
                volatile uint32_t i;
                volatile float temperature;
                volatile uint32_t pressure;
                
                res = bmp180_basic_init();
                if (res)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i=0; i<times; i++)
                {
                    bmp180_interface_delay_ms(1000);
                    res = bmp180_basic_read((float *)&temperature, (uint32_t *)&pressure);
                    if (res)
                    {
                        bmp180_basic_deinit();
                        
                        return 1;
                    }
                    bmp180_interface_debug_print("bmp180: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    bmp180_interface_debug_print("bmp180: temperature is %0.2fC.\n", temperature);
                    bmp180_interface_debug_print("bmp180: pressure is %dPa.\n", pressure);
                }
                bmp180_basic_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* param is invalid */
        else
        {
            return 5;
        }
    }

    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = bmp180(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        bmp180_interface_debug_print("bmp180: run failed.\n");
    }
    else if (res == 5)
    {
        bmp180_interface_debug_print("bmp180: param is invalid.\n");
    }
    else
    {
        bmp180_interface_debug_print("bmp180: unknow status code.\n");
    }

    return 0;
}
