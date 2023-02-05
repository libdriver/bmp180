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
 * @file      driver_bmp180.c
 * @brief     driver bmp180 source file
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

#include "driver_bmp180.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Bosch BMP180"        /**< chip name */
#define MANUFACTURER_NAME         "Bosch"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.8f                  /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                  /**< chip max supply voltage */
#define MAX_CURRENT               0.65f                 /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                 /**< chip max operating temperature */
#define DRIVER_VERSION            2000                  /**< driver version */

/**
 * @brief chip address definition
 */
#define BMP180_ADDRESS            0xEE        /**< iic device address */

/**
 * @brief chip register definition
 */
#define BMP180_REG_AC1_MSB          0xAA        /**< ac1 msb register */
#define BMP180_REG_AC1_LSB          0xAB        /**< ac1 lsb register */
#define BMP180_REG_AC2_MSB          0xAC        /**< ac2 msb register */
#define BMP180_REG_AC2_LSB          0xAD        /**< ac2 lsb register */
#define BMP180_REG_AC3_MSB          0xAE        /**< ac3 msb register */
#define BMP180_REG_AC3_LSB          0xAF        /**< ac3 lsb register */
#define BMP180_REG_AC4_MSB          0xB0        /**< ac4 msb register */
#define BMP180_REG_AC4_LSB          0xB1        /**< ac4 lsb register */
#define BMP180_REG_AC5_MSB          0xB2        /**< ac5 msb register */
#define BMP180_REG_AC5_LSB          0xB3        /**< ac5 lsb register */
#define BMP180_REG_AC6_MSB          0xB4        /**< ac6 msb register */
#define BMP180_REG_AC6_LSB          0xB5        /**< ac6 lsb register */
#define BMP180_REG_B1_MSB           0xB6        /**< b1 msb register */
#define BMP180_REG_B1_LSB           0xB7        /**< b1 lsb register */
#define BMP180_REG_B2_MSB           0xB8        /**< b2 msb register */
#define BMP180_REG_B2_LSB           0xB9        /**< b2 lsb register */
#define BMP180_REG_MB_MSB           0xBA        /**< mb msb register */
#define BMP180_REG_MB_LSB           0xBB        /**< mb lsb register */
#define BMP180_REG_MC_MSB           0xBC        /**< mc msb register */
#define BMP180_REG_MC_LSB           0xBD        /**< mc lsb register */
#define BMP180_REG_MD_MSB           0xBE        /**< md msb register */
#define BMP180_REG_MD_LSB           0xBF        /**< md lsb register */
#define BMP180_REG_CTRL_MEAS        0xF4        /**< ctrl meas register */
#define BMP180_REG_OUT_MSB          0xF6        /**< data out msb register */
#define BMP180_REG_OUT_LSB          0xF7        /**< data out lsb register */
#define BMP180_REG_OUT_XLSB         0xF8        /**< data xlsb register */
#define BMP180_REG_SOFT             0xE0        /**< soft reset register */
#define BMP180_REG_ID               0xD0        /**< chip id register */

/**
 * @brief      read bytes
 * @param[in]  *handle points to a bmp180 handle structure
 * @param[in]  addr is the iic device address
 * @param[in]  reg is the iic register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_bmp180_iic_read(bmp180_handle_t *handle, uint8_t addr, uint8_t reg, uint8_t *data)
{
    if (handle->iic_read(addr, reg, data, 1) != 0)        /* read */
    {
        return 1;                                         /* return error */
    }
    else
    {
        return 0;                                         /* success return 0 */
    }
}

/**
 * @brief     write bytes
 * @param[in] *handle points to a bmp180 handle structure
 * @param[in] addr is the iic device address
 * @param[in] reg is the iic register address
 * @param[in] data is the write data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_bmp180_iic_write(bmp180_handle_t *handle, uint8_t addr, uint8_t reg, uint8_t data)
{
    if (handle->iic_write(addr, reg, &data, 1) != 0)        /* write */
    {
        return 1;                                           /* return error */
    }
    else
    {
        return 0;                                           /* success return 0 */
    }
}

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
uint8_t bmp180_init(bmp180_handle_t *handle)
{
    uint8_t buf[22];
    int16_t temp1 = 0;
    uint16_t temp2 = 0;
    uint8_t id;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->debug_print == NULL)                                                     /* check debug_print */
    {
        return 3;                                                                        /* return error */
    }
    if (handle->iic_init == NULL)                                                        /* check iic_init */
    {
        handle->debug_print("bmp180: iic_init is null.\n");                              /* iic_init is nul */
        
        return 3;                                                                        /* return error */
    }
    if (handle->iic_deinit == NULL)                                                      /* check iic_deinit */
    {
        handle->debug_print("bmp180: iic_deinit is null.\n");                            /* iic_deinit is null */
        
        return 3;                                                                        /* return error */
    }
    if (handle->iic_read == NULL)                                                        /* check iic_read */
    {
        handle->debug_print("bmp180: iic_read is null.\n");                              /* iic_read is null */
        
        return 3;                                                                        /* return error */
    }
    if (handle->iic_write == NULL)                                                       /* check iic_write */
    {
        handle->debug_print("bmp180: iic_write is null.\n");                             /* iic_write is null */
        
        return 3;                                                                        /* return error */
    }
    if (handle->delay_ms == NULL)                                                        /* check delay_ms */
    {
        handle->debug_print("bmp180: delay_ms is null.\n");                              /* delay_ms is null */
        
        return 3;                                                                        /* return error */
    }
    
    if (handle->iic_init() != 0)                                                         /* iic init */
    {
        handle->debug_print("bmp180: iic init failed.\n");                               /* iic init failed */
        
        return 1;                                                                        /* return error */
    }
    if (a_bmp180_iic_read(handle, BMP180_ADDRESS, BMP180_REG_ID, (uint8_t *)&id) != 0)   /* read chip id */
    {
        handle->debug_print("bmp180: read id failed.\n");                                /* read id failed */
        (void)handle->iic_deinit();                                                      /* iic deinit */
        
        return 1;                                                                        /* return error */
    }
    if (id != 0x55)                                                                      /* check id */
    {
        handle->debug_print("bmp180: id is error.\n");                                   /* id is error */
        (void)handle->iic_deinit();                                                      /* iic deinit */
        
        return 4;                                                                        /* return error */
    }
    if (handle->iic_read(BMP180_ADDRESS, BMP180_REG_AC1_MSB, (uint8_t *)buf, 22) != 0)   /* read ac1-md */
    {
        handle->debug_print("bmp180: read AC1_MSB-MD_LSB failed.\n");                    /* read ac1 -md failed */
        (void)handle->iic_deinit();                                                      /* deinit iic */
        
        return 5;                                                                        /* return error */
    }
    temp1 = buf[0] << 8;                                                                 /* get MSB */
    temp1 = temp1 | buf[1];                                                              /* get LSB */
    handle->ac1 = temp1;                                                                 /* save ac1 */
    temp1 = 0;                                                                           /* reset temp1 */
    temp1 = buf[2] << 8;                                                                 /* get MSB */
    temp1 = temp1 | buf[3];                                                              /* get LSB */
    handle->ac2 = temp1;                                                                 /* save ac2 */
    temp1 = 0;                                                                           /* reset temp1 */
    temp1 = buf[4] << 8;                                                                 /* get MSB */
    temp1 = temp1 | buf[5];                                                              /* get LSB */
    handle->ac3 = temp1;                                                                 /* save ac3 */
    temp1 = 0;                                                                           /* reset temp1 */
    temp2 = buf[6] << 8;                                                                 /* get MSB */
    temp2 = temp2 | buf[7];                                                              /* get LSB */
    handle->ac4 = temp2;                                                                 /* save ac4 */
    temp2 = 0;                                                                           /* reset temp1 */
    temp2 = buf[8] << 8;                                                                 /* get MSB */
    temp2 = temp2 | buf[9];                                                              /* get LSB */
    handle->ac5 = temp2;                                                                 /* save ac5 */
    temp2 = 0;                                                                           /* reset temp2 */
    temp2 = buf[10] << 8;                                                                /* get MSB */
    temp2 = temp2 | buf[11];                                                             /* get LSB */
    handle->ac6 = temp2;                                                                 /* save ac6 */
    temp1 = buf[12] << 8;                                                                /* get MSB */
    temp1 = temp1 | buf[13];                                                             /* get LSB */
    handle->b1 = temp1;                                                                  /* save b1 */
    temp1 = 0;                                                                           /* reset temp1 */
    temp1 = buf[14] << 8;                                                                /* get MSB */
    temp1 = temp1 | buf[15];                                                             /* get LSB */
    handle->b2 = temp1;                                                                  /* save b2 */
    temp1 = 0;                                                                           /* reset temp1 */
    temp1 = buf[16] << 8;                                                                /* get MSB */
    temp1 = temp1 | buf[17];                                                             /* get LSB */
    handle->mb = temp1;                                                                  /* save mb */
    temp1 = 0;                                                                           /* reset temp1 */
    temp1 = buf[18] << 8;                                                                /* get MSB */
    temp1 = temp1 | buf[19];                                                             /* get LSB */
    handle->mc = temp1;                                                                  /* save mc */
    temp1 = 0;                                                                           /* reset temp1 */
    temp1 = buf[20] << 8;                                                                /* get MSB */
    temp1 = temp1 | buf[21];                                                             /* get LSB */
    handle->md = temp1;                                                                  /* save md */
    handle->inited = 1;                                                                  /* flag finish initialization */
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t bmp180_deinit(bmp180_handle_t *handle)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    if (handle->iic_deinit() != 0)                                  /* iic deinit */
    {
        handle->debug_print("bmp180: iic deinit failed.\n");        /* iic deinit failed */
        
        return 1;                                                   /* return error */
    }   
    handle->inited = 0;                                             /* flag close */
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t bmp180_set_mode(bmp180_handle_t *handle, bmp180_mode_t mode)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    handle->oss = (uint8_t)mode;        /* set mode */
    
    return 0;                           /* success return 0 */
}

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
uint8_t bmp180_get_mode(bmp180_handle_t *handle, bmp180_mode_t *mode)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    if (handle->inited != 1)                   /* check handle initialization */
    {
        return 3;                              /* return error */
    }
    
    *mode = (bmp180_mode_t)handle->oss;        /* get mode */
    
    return 0;                                  /* success return 0 */
}

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
uint8_t bmp180_read_pressure(bmp180_handle_t *handle, uint32_t *raw, uint32_t *pa)
{
    uint8_t buf[3];
    uint8_t status;
    uint16_t num;
    int32_t ut = 0, up = 0, x1 ,x2, x3, b5, b6, b3, p;
    uint32_t b4,b7;
    
    if (handle == NULL)                                                                                /* check handle */
    {
        return 2;                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                           /* check handle initialization */
    {
        return 3;                                                                                      /* return error */
    }
    
    num = 5000;                                                                                        /* set timeout 5000 ms */
    if (a_bmp180_iic_write(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, 0x2E) != 0)                   /* write temperature measurement command */
    {
        handle->debug_print("bmp180: write CTRL_MEAS failed.\n");                                      /* write CTRL_MEAS failed */
        
        return 1;                                                                                      /* return error */
    }
    while (num != 0)                                                                                   /* check times */
    {
        handle->delay_ms(1);                                                                           /* wait 1 ms */
        if (a_bmp180_iic_read(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, (uint8_t *)&status) != 0)  /* read ctrl status */
        {
            handle->debug_print("bmp180: read CTRL_MEAS failed.\n");                                   /* return ctrl meas failed */
            
            return 1;                                                                                  /* return error */
        }
        status = status & 0x20;                                                                        /* get finished flag */
        if (status == 0)                                                                               /* check flag */
        {
            goto t_read;                                                                               /* goto next step */
        }
        else
        {
            num = num-1;                                                                               /* times-1 */
        }
    }
    handle->debug_print("bmp180: read temperature failed.\n");                                         /* read temperature failed */
    
    return 1;                                                                                          /* return error */
    
    t_read:
    memset(buf, 0, sizeof(uint8_t) * 3);                                                               /* clear the buffer */
    if (handle->iic_read(BMP180_ADDRESS, BMP180_REG_OUT_MSB, (uint8_t *)buf ,2) != 0)                  /* read raw temperature */
    {
        handle->debug_print("bmp180: read OUT MSB LSB failed.\n");                                     /* read OUT MSB LSB failed */
        
        return 1;                                                                                      /* return error */
    }
    ut = buf[0] << 8;                                                                                  /* get MSB */
    ut = ut | buf[1];                                                                                  /* get LSB */
    ut = ut & 0x0000FFFFU;                                                                             /* get valid part */
    if (a_bmp180_iic_write(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, 0x34+(handle->oss<<6)) != 0)  /* write pressure measurement command */
    {
        handle->debug_print("bmp180: write CTRL_MEAS failed.\n");                                      /* write CTRL_MEAS failed */
        
        return 1;                                                                                      /* return error */
    }
    num = 5000;                                                                                        /* set timeout 5000 ms */
    while (num != 0)                                                                                   /* check times */
    {
        handle->delay_ms(1);                                                                           /* wait 1 ms */
        if (a_bmp180_iic_read(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, (uint8_t *)&status) != 0)  /* read status */
        {
            handle->debug_print("bmp180: read CTRL_MEAS failed.\n");                                   /* read CTRL_MEAS failed */
            
            return 1;                                                                                  /* return error */
        }
        status = status & 0x20;                                                                        /* get finished flag */
        if (status == 0)                                                                               /* check flag */
        {
            goto p_read;                                                                               /* goto next step */
        }
        else
        {
            num = num-1;                                                                               /* times-1 */
        }
    }
    handle->debug_print("bmp180: read pressure failed.\n");                                            /* read pressure failed */
    
    return 1;                                                                                          /* return error */
    
    p_read:
    memset(buf, 0, sizeof(uint8_t) * 3);                                                               /* clear the buffer */
    if (handle->iic_read(BMP180_ADDRESS, BMP180_REG_OUT_MSB, (uint8_t *)buf ,3) != 0)                  /* read pressure */
    {
        handle->debug_print("bmp180: read OUT MSB LSB XLSB failed.\n");                                /* read OUT MSB LSB XLSB failed */
        
        return 1;                                                                                      /* return error */
    }
    up = buf[0] << 8;                                                                                  /* get MSB */
    up = up | buf[1];                                                                                  /* get LSB */
    up = up << 8;                                                                                      /* left shift 8 */
    up = up | buf[2];                                                                                  /* get XLSB */
    *raw = up;                                                                                         /* get raw data */
    up = up >> (8-handle->oss);                                                                        /* shift */
    if (handle->oss == 0)                                                                              /* ultra low */
    {
        up = up & 0x0000FFFFU;                                                                         /* set mask */
    }
    else if (handle->oss == 1)                                                                         /* standard */
    {
        up = up & 0x0001FFFFU;                                                                         /* set mask */
    }
    else if (handle->oss == 2)                                                                         /* high */
    {
        up= up & 0x0003FFFFU;                                                                          /* set mask */
    }
    else if (handle->oss == 3)                                                                         /* ultra high */
    {
        up = up & 0x0007FFFFU;                                                                         /* set mask */
    }
    else
    {
        handle->debug_print("bmp180: oss param error.\n");                                             /* oss param error */
        
        return 1;                                                                                      /* return error */
    }
    x1 = (((ut - (int32_t)handle->ac6) * (int32_t)handle->ac5)) >> 15;                                 /* calculate x1 */
    x2 = (int32_t)((((int32_t)handle->mc) << 11) / (x1 + (int32_t)handle->md));                        /* calculate x2 */
    b5 = x1 + x2;                                                                                      /* calculate b5 */
    b6 = b5 - 4000;                                                                                    /* calculate b6 */
    x1 = ((int32_t)handle->b2 * ((b6 * b6) >> 12)) >> 11;                                              /* calculate x1 */
    x2 = ((int32_t)handle->ac2 * b6) >> 11;                                                            /* calculate x2 */
    x3 = x1 + x2;                                                                                      /* calculate x3 */
    b3 = (((((int32_t)handle->ac1) * 4 + x3) << handle->oss) + 2) >> 2;                                /* calculate b3 */
    x1 = ((int32_t)handle->ac3 * b6) >> 13;                                                            /* calculate x1 */
    x2 = ((int32_t)handle->b1*(((b6 * b6)) >> 12)) >> 16;                                              /* calculate x2 */
    x3 = ((x1 + x2) + 2) >> 2;                                                                         /* calculate x3 */
    b4 = (uint32_t)((((uint32_t)handle->ac4 * (uint32_t)(x3 + 32768))) >> 15);                         /* calculate b4 */
    b7 = (uint32_t)((uint32_t)(up - b3) * (50000>>handle->oss));                                       /* calculate b7 */
    if (b7 < 0x80000000U)
    {
        p = (int32_t)((b7 << 1) / b4);                                                                 /* calculate p */
    }
    else
    {
        p = (int32_t)((b7 / b4) << 1);                                                                 /* calculate p */
    }
    x1 = (p >> 8) * (p >> 8);                                                                          /* calculate x1 */
    x1 = (x1 * 3038) >> 16;                                                                            /* calculate x1 */
    x2 = (-7357 * p) >> 16;                                                                            /* calculate x2 */
    *pa = p + ((x1 + x2 + 3791) >> 4);                                                                 /* calculate x2 */
    
    return 0;                                                                                          /* success return 0 */
}

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
uint8_t bmp180_read_temperature(bmp180_handle_t *handle, uint16_t *raw, float *c)
{
    uint8_t buf[3];
    uint8_t status;
    uint16_t num;
    int32_t ut = 0, x1 ,x2, b5;
    
    if (handle == NULL)                                                                                /* check handle */
    {
        return 2;                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                           /* check handle initialization */
    {
        return 3;                                                                                      /* return error */
    }
    
    num = 5000;                                                                                        /* set timeout 5000 */
    if (a_bmp180_iic_write(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, 0x2E) != 0)                   /* write temperature measurement command */
    {
        handle->debug_print("bmp180: write CTRL_MEAS failed.\n");                                      /* write CTRL_MEAS failed */
        
        return 1;                                                                                      /* return error */
    }
    while (num != 0)                                                                                   /* check times */
    {
        handle->delay_ms(1);                                                                           /* delay 1 ms */
        if (a_bmp180_iic_read(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, (uint8_t *)&status) != 0)  /* read status */
        {
            handle->debug_print("bmp180: read CTRL_MEAS failed.\n");                                   /* read CTRL_MEAS failed */
            
            return 1;                                                                                  /* return error */
        }
        status = status & 0x20;                                                                        /* get finished flag */
        if (status == 0)                                                                               /* check flag */
        {
            goto t_read;                                                                               /* goto next step */
        }
        else
        {
            num = num-1;                                                                               /* times-1 */
        }
    }
    handle->debug_print("bmp180: read temperature failed.\n");                                         /* read temperature failed */
    
    return 1;                                                                                          /* return error */
    
    t_read:
    memset(buf, 0, sizeof(uint8_t) * 3);                                                               /* clear the buffer */
    if (handle->iic_read(BMP180_ADDRESS, BMP180_REG_OUT_MSB, (uint8_t *)buf ,2) != 0)                  /* read raw temperature */
    {
        handle->debug_print("bmp180: read OUT MSB LSB failed.\n");                                     /* read OUT MSB LSB failed */
        
        return 1;                                                                                      /* return error */
    }
    ut = buf[0] << 8;                                                                                  /* get MSB */
    ut = ut | buf[1];                                                                                  /* get LSB */
    ut = ut & 0x0000FFFFU;                                                                             /* set mask */
    *raw = (uint16_t)ut;                                                                               /* get raw temperature */
    x1 = (((ut - (int32_t)handle->ac6) * (int32_t)handle->ac5)) >> 15;                                 /* calculate x1 */
    x2 =(int32_t)((((int32_t)handle->mc) << 11) / (x1 + (int32_t)handle->md));                         /* calculate x2 */
    b5 = x1 + x2;                                                                                      /* calculate b5 */
    *c = ((uint16_t)((b5 + 8) >> 4)) * 0.1f;                                                           /* calculate temperature */
    
    return 0;                                                                                          /* success return 0 */
}

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
                                         uint32_t *pressure_raw, uint32_t *pressure_pa)
{
    uint8_t buf[3];
    uint8_t status;
    uint16_t num;
    int32_t ut = 0, up = 0, x1 ,x2, x3, b5, b6, b3, p;
    uint32_t b4,b7;
    
    if (handle == NULL)                                                                                /* check handle */
    {
        return 2;                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                           /* check handle initialization */
    {
        return 3;                                                                                      /* return error */
    }
    
    num = 5000;                                                                                        /* set timeout 5000 */
    if (a_bmp180_iic_write(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, 0x2E) != 0)                   /* write temperature measurement command */
    {
        handle->debug_print("bmp180: write CTRL_MEAS failed.\n");                                      /* write CTRL_MEAS failed */
        
        return 1;                                                                                      /* return error */
    }
    while (num != 0)                                                                                   /* check times */
    {
        handle->delay_ms(1);                                                                           /* wait 1 ms */
        if (a_bmp180_iic_read(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, (uint8_t *)&status) != 0)  /* read status */
        {
            handle->debug_print("bmp180: read CTRL_MEAS failed.\n");                                   /* read CTRL_MEAS failed */
            
            return 1;                                                                                  /* return error */
        }
        status = status & 0x20;                                                                        /* get finished flag */
        if (status == 0)                                                                               /* check flag */
        {
            goto t_read;                                                                               /* goto next step */
        }
        else
        {
            num = num-1;                                                                               /* times-1 */
        }
    }
    handle->debug_print("bmp180: read temperature failed.\n");                                         /* read temperature failed */
    
    return 1;                                                                                          /* return error */
    
    t_read:
    memset(buf, 0, sizeof(uint8_t) * 3);                                                               /* clear the buffer */
    if (handle->iic_read(BMP180_ADDRESS, BMP180_REG_OUT_MSB, (uint8_t *)buf ,2) != 0)                  /* read raw temperature */
    {
        handle->debug_print("bmp180: read OUT MSB LSB failed.\n");                                     /* read OUT MSB LSB failed */
        
        return 1;                                                                                      /* return error */
    }
    ut = buf[0] << 8;                                                                                  /* get MSB */
    ut = ut | buf[1];                                                                                  /* get LSB */
    ut = ut & 0x0000FFFFU;                                                                             /* set mask */
    *temperature_raw = (uint16_t)ut;                                                                   /* get temperature */
    if (a_bmp180_iic_write(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, 0x34+(handle->oss<<6)) != 0)  /* write pressure measurement command */
    {
        handle->debug_print("bmp180: write CTRL_MEAS failed.\n");                                      /* write CTRL_MEAS failed */
        
        return 1;                                                                                      /* return error */
    }    
    num = 5000;                                                                                        /* set timeout 5000 */
    while (num != 0)                                                                                   /* check times */
    {
        handle->delay_ms(1);                                                                           /* wait 1 ms */
        if (a_bmp180_iic_read(handle, BMP180_ADDRESS, BMP180_REG_CTRL_MEAS, (uint8_t *)&status) != 0)  /* read status */
        {
            handle->debug_print("bmp180: read CTRL_MEAS failed.\n");                                   /* read CTRL_MEAS failed */
            
            return 1;                                                                                  /* return error */
        }
        status = status & 0x20;                                                                        /* get finished flag */
        if (status == 0)                                                                               /* check flag */
        {
            goto p_read;                                                                               /* goto next step */
        }
        else
        {
            num = num-1;                                                                               /* times-1 */
        }
    }
    handle->debug_print("bmp180: read pressure failed.\n");                                            /* read pressure failed */

    return 1;                                                                                          /* return error */
    
    p_read:
    memset(buf, 0, sizeof(uint8_t) * 3);                                                               /* clear the buffer */
    if (handle->iic_read(BMP180_ADDRESS, BMP180_REG_OUT_MSB, (uint8_t *)buf ,3) != 0)                  /* read raw pressure */
    {
        handle->debug_print("bmp180: read OUT MSB LSB XLSB failed.\n");                                /* read OUT MSB LSB XLSB failed */
        
        return 1;                                                                                      /* return error */
    }    
    up = buf[0] << 8;                                                                                  /* get MSB */
    up = up | buf[1];                                                                                  /* get LSB */
    up = up << 8;                                                                                      /* left shit */
    up = up | buf[2];                                                                                  /* get XLSB */
    *pressure_raw = up;                                                                                /* get pressure */
    up = up >> (8-handle->oss);                                                                        /* right shift */
    if (handle->oss == 0)                                                                              /* ultra low */
    {
        up = up & 0x0000FFFFU;                                                                         /* set mask */
    }
    else if (handle->oss == 1)                                                                         /* standard */
    {
        up = up & 0x0001FFFFU;                                                                         /* set mask */
    }
    else if (handle->oss == 2)                                                                         /* high */
    {
        up= up & 0x0003FFFFU;                                                                          /* set mask */
    }
    else if (handle->oss == 3)                                                                         /* ultra high */
    {
        up = up & 0x0007FFFFU;                                                                         /* set mask */
    }
    else
    {
        handle->debug_print("bmp180: oss param error.\n");                                             /* oss param error */
        
        return 1;                                                                                      /* return error */
    }
    x1 = (((ut - (int32_t)handle->ac6) * (int32_t)handle->ac5)) >> 15;                                 /* calculate x1 */
    x2 = (int32_t)((((int32_t)handle->mc) << 11) / (x1 + (int32_t)handle->md));                        /* calculate x2 */
    b5 = x1 + x2;                                                                                      /* calculate b5 */
    *temperature_c = ((uint16_t)((b5 + 8) >> 4)) * 0.1f;                                               /* get temperature */
    b6 = b5 - 4000;                                                                                    /* calculate b6 */
    x1 = ((int32_t)handle->b2 * ((b6 * b6) >> 12)) >> 11;                                              /* calculate x1 */
    x2 = ((int32_t)handle->ac2 * b6) >> 11;                                                            /* calculate x2 */
    x3 = x1 + x2;                                                                                      /* calculate x3 */
    b3 = (((((int32_t)handle->ac1) * 4 + x3)<<handle->oss) + 2) >> 2;                                  /* calculate b3 */
    x1 = ((int32_t)handle->ac3 * b6) >> 13;                                                            /* calculate x1 */
    x2 = ((int32_t)handle->b1 * (((b6 * b6)) >> 12)) >> 16;                                            /* calculate x2 */
    x3 = ((x1 + x2) + 2) >> 2;                                                                         /* calculate x3 */
    b4 = (uint32_t)((((uint32_t)handle->ac4 * (uint32_t)(x3 + 32768))) >> 15);                         /* calculate b4 */
    b7 = (uint32_t)((uint32_t)(up - b3) * (50000 >> handle->oss));                                     /* calculate b7 */
    if (b7 < 0x80000000U)
    {
        p = (int32_t)((b7 << 1) / b4);                                                                 /* calculate p */
    }
    else
    {
        p = (int32_t)((b7 / b4) << 1);                                                                 /* calculate p */
    }
    x1 = (p >> 8) * (p >> 8);                                                                          /* calculate x1 */
    x1 = (x1 * 3038) >> 16;                                                                            /* calculate x1 */
    x2 = (-7357 * p) >> 16;                                                                            /* calculate x2 */
    *pressure_pa = p + ((x1 + x2 + 3791) >> 4);                                                        /* set pressure */
    
    return 0;                                                                                          /* success return 0 */
}

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
uint8_t bmp180_set_reg(bmp180_handle_t *handle, uint8_t reg, uint8_t value)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    } 

    return a_bmp180_iic_write(handle, BMP180_ADDRESS, reg, value);       /* write register */
}

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
uint8_t bmp180_get_reg(bmp180_handle_t *handle, uint8_t reg, uint8_t *value)
{
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    } 

    return a_bmp180_iic_read(handle, BMP180_ADDRESS, reg, value);       /* read register */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a bmp180 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bmp180_info(bmp180_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(bmp180_info_t));                         /* initialize bmp180 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
