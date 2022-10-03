### 1. Chip

#### 1.1 Chip Info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

### 2. Shell

#### 2.1 Shell Parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. BMP180

#### 3.1 Command Instruction

​          bmp180 is a basic command which can test all bmp180 driver function:

​           -i         show bmp180 chip and driver information.

​           -h        show bmp180 help.

​           -p        show bmp180 pin connections of the current board.

​           -t (reg | read <times>) 

​           -t reg        run bmp180 register test.

​           -t read <times>        run bmp180 read test. times means test times.         

​           -c read <times>        run bmp180 read function.times means read times.

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
bmp180 -t read 3

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
bmp180: ultra low mode temperature: 25.0C.
bmp180: ultra low mode pressure: 102562Pa.
bmp180: ultra low mode temperature: 25.0C.
bmp180: ultra low mode pressure: 102565Pa.
bmp180: ultra low mode temperature: 25.0C.
bmp180: ultra low mode pressure: 102565Pa.
bmp180: standard mode temperature: 25.0C.
bmp180: standard mode pressure: 102566Pa.
bmp180: standard mode temperature: 25.0C.
bmp180: standard mode pressure: 102566Pa.
bmp180: standard mode temperature: 25.0C.
bmp180: standard mode pressure: 102560Pa.
bmp180: high mode temperature: 25.0C.
bmp180: high mode pressure: 102567Pa.
bmp180: high mode temperature: 25.0C.
bmp180: high mode pressure: 102563Pa.
bmp180: high mode temperature: 25.0C.
bmp180: high mode pressure: 102566Pa.
bmp180: ultra highmode temperature: 25.0C.
bmp180: ultra highmode pressure: 102573Pa.
bmp180: ultra highmode temperature: 25.0C.
bmp180: ultra highmode pressure: 102563Pa.
bmp180: ultra highmode temperature: 25.0C.
bmp180: ultra highmode pressure: 102571Pa.
bmp180: finish read test.
```

```shell
bmp180 -c read 3

bmp180: 1/3.
bmp180: temperature is 24.90C.
bmp180: pressure is 102387Pa.
bmp180: 2/3.
bmp180: temperature is 24.90C.
bmp180: pressure is 102370Pa.
bmp180: 3/3.
bmp180: temperature is 24.90C.
bmp180: pressure is 102373Pa.
```

```shell
bmp180 -h

bmp180 -i
	show bmp180 chip and driver information.
bmp180 -h
	show bmp180 help.
bmp180 -p
	show bmp180 pin connections of the current board.
bmp180 -t reg
	run bmp180 register test.
bmp180 -t read <times>
	run bmp180 read test.times means test times.
bmp180 -c read <times>
	run bmp180 read function.times means read times.
```

