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
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     bmp180 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t bmp180(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running times */
            case 1 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (bmp180_register_test() != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (bmp180_read_test(times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float temperature;
        uint32_t pressure;
        
        /* basic init */
        res = bmp180_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            bmp180_interface_delay_ms(1000);
            
            /* read data */
            res = bmp180_basic_read((float *)&temperature, (uint32_t *)&pressure);
            if (res != 0)
            {
                (void)bmp180_basic_deinit();
                
                return 1;
            }
            
            /* output */
            bmp180_interface_debug_print("bmp180: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            bmp180_interface_debug_print("bmp180: temperature is %0.2fC.\n", temperature);
            bmp180_interface_debug_print("bmp180: pressure is %dPa.\n", pressure);
        }
        
        /* deinit */
        (void)bmp180_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        bmp180_interface_debug_print("Usage:\n");
        bmp180_interface_debug_print("  bmp180 (-i | --information)\n");
        bmp180_interface_debug_print("  bmp180 (-h | --help)\n");
        bmp180_interface_debug_print("  bmp180 (-p | --port)\n");
        bmp180_interface_debug_print("  bmp180 (-t reg | --test=reg)\n");
        bmp180_interface_debug_print("  bmp180 (-t read | --test=read) [--times=<num>]\n");
        bmp180_interface_debug_print("  bmp180 (-e read | --example=read) [--times=<num>]\n");
        bmp180_interface_debug_print("\n");
        bmp180_interface_debug_print("Options:\n");
        bmp180_interface_debug_print("  -e <read>, --example=<read>     Run the driver example.\n");
        bmp180_interface_debug_print("  -h, --help                      Show the help.\n");
        bmp180_interface_debug_print("  -i, --information               Show the chip information.\n");
        bmp180_interface_debug_print("  -p, --port                      Display the pin connections of the current board.\n");
        bmp180_interface_debug_print("  -t <reg | read>, --test=<reg | read>\n");
        bmp180_interface_debug_print("                                  Run the driver test.\n");
        bmp180_interface_debug_print("      --times=<num>               Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        bmp180_info_t info;
        
        /* print bmp180 info */
        bmp180_info(&info);
        bmp180_interface_debug_print("bmp180: chip is %s.\n", info.chip_name);
        bmp180_interface_debug_print("bmp180: manufacturer is %s.\n", info.manufacturer_name);
        bmp180_interface_debug_print("bmp180: interface is %s.\n", info.interface);
        bmp180_interface_debug_print("bmp180: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bmp180_interface_debug_print("bmp180: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bmp180_interface_debug_print("bmp180: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bmp180_interface_debug_print("bmp180: max current is %0.2fmA.\n", info.max_current_ma);
        bmp180_interface_debug_print("bmp180: max temperature is %0.1fC.\n", info.temperature_max);
        bmp180_interface_debug_print("bmp180: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        bmp180_interface_debug_print("bmp180: SCL connected to GPIO3(BCM).\n");
        bmp180_interface_debug_print("bmp180: SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
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
        bmp180_interface_debug_print("bmp180: unknown status code.\n");
    }

    return 0;
}
