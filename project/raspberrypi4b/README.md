### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(bmp180 REQUIRED)
```

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
./bmp180 -i

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
./bmp180 -p

bmp180: SCL connected to GPIO3(BCM).
bmp180: SDA connected to GPIO2(BCM).
```

```shell
./bmp180 -t reg

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
./bmp180 -t read --times=3

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
bmp180: ultra low mode temperature: 28.4C.
bmp180: ultra low mode pressure: 101468Pa.
bmp180: ultra low mode temperature: 28.4C.
bmp180: ultra low mode pressure: 101459Pa.
bmp180: ultra low mode temperature: 28.3C.
bmp180: ultra low mode pressure: 101465Pa.
bmp180: standard mode temperature: 28.3C.
bmp180: standard mode pressure: 101462Pa.
bmp180: standard mode temperature: 28.2C.
bmp180: standard mode pressure: 101456Pa.
bmp180: standard mode temperature: 28.2C.
bmp180: standard mode pressure: 101460Pa.
bmp180: high mode temperature: 28.2C.
bmp180: high mode pressure: 101460Pa.
bmp180: high mode temperature: 28.1C.
bmp180: high mode pressure: 101460Pa.
bmp180: high mode temperature: 28.1C.
bmp180: high mode pressure: 101470Pa.
bmp180: ultra highmode temperature: 28.1C.
bmp180: ultra highmode pressure: 101458Pa.
bmp180: ultra highmode temperature: 28.1C.
bmp180: ultra highmode pressure: 101461Pa.
bmp180: ultra highmode temperature: 28.0C.
bmp180: ultra highmode pressure: 101462Pa.
bmp180: finish read test.
```

```shell
./bmp180 -e read --times=3

bmp180: 1/3.
bmp180: temperature is 27.20C.
bmp180: pressure is 101459Pa.
bmp180: 2/3.
bmp180: temperature is 27.20C.
bmp180: pressure is 101459Pa.
bmp180: 3/3.
bmp180: temperature is 27.20C.
bmp180: pressure is 101457Pa.
```

```shell
./bmp180 -h

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

