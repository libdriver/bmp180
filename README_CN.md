<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver BMP180

[English](/README.md) | [ 简体中文](/README_CH.md)

BMP180是BMP085的功能兼容后继产品，是新一代高性能消费类应用的精密数字压力传感器。BMP180的超低功耗、低电压供电经过特别优化设计，可用于移动电话、PDA、GPS导航设备和户外设备。在只有0.25米的低海拔条件下拥有快速转换时间，BMP180提供卓越的性能。I2C接口允许与微控制器系统集成。BMP180基于压阻技术，具有EMC鲁棒性、高精度和线性度以及长期稳定。

LibDriver BMP180是LibDriver推出的BMP180的全功能驱动，该驱动提供温度、压力读取和模式设置等功能。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver BMP180的源文件。

/interface目录包含了LibDriver BMP180与平台无关的IIC总线模板。

/test目录包含了LibDriver BMP180驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver BMP180编程范例。

/doc目录包含了LibDriver BMP180离线文档。

/datasheet目录包含了BMP180数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，/interface目录和/example目录加入工程。

### 使用

#### example basic

```C
uint8_t res;
uint32_t i;
float temperature;
uint32_t pressure;

res = bmp180_basic_init();
if (res)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    bmp180_interface_delay_ms(1000);
    res = bmp180_basic_read((float *)&temperature, (uint32_t *)&pressure);
    if (res)
    {
        bmp180_basic_deinit();

        return 1;
    }
    bmp180_interface_debug_print("bmp180: temperature is %0.2fC.\n", temperature);
    bmp180_interface_debug_print("bmp180: pressure is %dPa.\n", pressure);
    
    ...
        
}

...

bmp180_basic_deinit();

return 0;
```

### 文档

在线文档: https://www.libdriver.com/docs/bmp180/index.html

离线文档: /doc/html/index.html

### 贡献

请联系lishifenging@outlook.com

### 版权

版权(C) LibDriver 2015-2021 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com