### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. BMP180

#### 3.1 Command Instruction

1. Show bmp180 chip and driver information.

   ```shell
   bmp180 (-i | --information)
   ```

2. Show bmp180 help.

   ```shell
   bmp180 (-h | --help)
   ```

3. Show bmp180 pin connections of the current board.

   ```shell
   bmp180 (-p | --port)
   ```

4. Run bmp180 register test.

   ```shell
   bmp180 (-t reg | --test=reg)
   ```

5. Run bmp180 read test, num means test times. 

   ```shell
   bmp180 (-t read | --test=read) [--times=<num>]
   ```

6. Run bmp180 read function, num means read times.

   ```shell
   bmp180 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
bmp180 -i

bmp180: chip is Bosch BMP180.
bmp180: manufacturer is Bosch.
bmp180: interface is IIC.
bmp180: driver version is 2.0.
bmp180: min supply voltage is 1.8V.
bmp180: max supply voltage is 3.6V.
bmp180: max current is 0.65mA.
bmp180: max temperature is 85.0C.
bmp180: min temperature is -40.0C.
```

```shell
bmp180 -p

bmp180: SCL connected to GPIOB PIN8.
bmp180: SDA connected to GPIOB PIN9.
```

```shell
bmp180 -t reg

bmp180: chip is Bosch BMP180.
bmp180: manufacturer is Bosch.
bmp180: interface is IIC.
bmp180: driver version is 2.0.
bmp180: min supply voltage is 1.8V.
bmp180: max supply voltage is 3.6V.
bmp180: max current is 0.65mA.
bmp180: max temperature is 85.0C.
bmp180: min temperature is -40.0C.
bmp180: start register test.
bmp180: bmp180_set_mode/bmp180_get_mode test.
bmp180: set ultra low mode.
bmp180: check mode ok.
bmp180: set standard mode.
bmp180: check mode ok.
bmp180: set high mode.
bmp180: check mode ok.
bmp180: set ultra high mode.
bmp180: check mode ok.
bmp180: finish register test.
```

```shell
bmp180 -t read --times=3

bmp180: chip is Bosch BMP180.
bmp180: manufacturer is Bosch.
bmp180: interface is IIC.
bmp180: driver version is 2.0.
bmp180: min supply voltage is 1.8V.
bmp180: max supply voltage is 3.6V.
bmp180: max current is 0.65mA.
bmp180: max temperature is 85.0C.
bmp180: min temperature is -40.0C.
bmp180: start read test.
bmp180: ultra low mode temperature: 28.6C.
bmp180: ultra low mode pressure: 101463Pa.
bmp180: ultra low mode temperature: 28.6C.
bmp180: ultra low mode pressure: 101457Pa.
bmp180: ultra low mode temperature: 28.5C.
bmp180: ultra low mode pressure: 101457Pa.
bmp180: standard mode temperature: 28.5C.
bmp180: standard mode pressure: 101467Pa.
bmp180: standard mode temperature: 28.5C.
bmp180: standard mode pressure: 101449Pa.
bmp180: standard mode temperature: 28.4C.
bmp180: standard mode pressure: 101455Pa.
bmp180: high mode temperature: 28.4C.
bmp180: high mode pressure: 101460Pa.
bmp180: high mode temperature: 28.3C.
bmp180: high mode pressure: 101462Pa.
bmp180: high mode temperature: 28.3C.
bmp180: high mode pressure: 101454Pa.
bmp180: ultra highmode temperature: 28.3C.
bmp180: ultra highmode pressure: 101456Pa.
bmp180: ultra highmode temperature: 28.2C.
bmp180: ultra highmode pressure: 101458Pa.
bmp180: ultra highmode temperature: 28.2C.
bmp180: ultra highmode pressure: 101460Pa.
bmp180: finish read test.
```

```shell
bmp180 -e read --times=3

bmp180: 1/3.
bmp180: temperature is 28.80C.
bmp180: pressure is 101470Pa.
bmp180: 2/3.
bmp180: temperature is 28.70C.
bmp180: pressure is 101461Pa.
bmp180: 3/3.
bmp180: temperature is 28.60C.
bmp180: pressure is 101457Pa.
```

```shell
bmp180 -h

Usage:
  bmp180 (-i | --information)
  bmp180 (-h | --help)
  bmp180 (-p | --port)
  bmp180 (-t reg | --test=reg)
  bmp180 (-t read | --test=read) [--times=<num>]
  bmp180 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>     Run the driver example.
  -h, --help                      Show the help.
  -i, --information               Show the chip information.
  -p, --port                      Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                                  Run the driver test.
      --times=<num>               Set the running times.([default: 3])
```

