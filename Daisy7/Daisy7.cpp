/*
 * Daniele Sdei, Marco Antonini 2012 Madefree Electronics (www.madefree.eu)
 *
 * HMC5883L section is based on code by Love Electronics (loveelectronics.co.uk)
 * BMP085 section is based on code by Jim Lindblom
 * 
 */

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h" 
#endif

#include "Daisy7.h"

Daisy7::Daisy7()
{
  //Costructor
}

void Daisy7::begin()
{
  Wire.begin();
    
  /*****  HMC5883 Magnetometer *****/
  m_Scale = 1;
    
  /*****  BMP085 Temperature\Baramoter *****/
  BaroCalibration();
    
  /*****  LIS331DLH Accelerometer *****/
  AccConfig();
    
  /*****  L3G4200D Gyroscope *****/
  GyroEnableDefault();
}


/*****  HMC5883 Magnetometer *****/

MagnetometerRaw Daisy7::MagnReadRawAxis()
{
  uint8_t* buffer = MagnRead(DataRegisterBegin, 6);
  MagnetometerRaw raw = MagnetometerRaw();
  raw.XAxis = (buffer[0] << 8) | buffer[1];
  raw.ZAxis = (buffer[2] << 8) | buffer[3];
  raw.YAxis = (buffer[4] << 8) | buffer[5];
  return raw;
}

MagnetometerScaled Daisy7::MagnReadScaledAxis()
{
  MagnetometerRaw raw = MagnReadRawAxis();
  MagnetometerScaled scaled = MagnetometerScaled();
  scaled.XAxis = raw.XAxis * m_Scale;
  scaled.ZAxis = raw.ZAxis * m_Scale;
  scaled.YAxis = raw.YAxis * m_Scale;
  return scaled;
}

int Daisy7::MagnSetScale(float gauss)
{
	uint8_t regValue = 0x00;
	if(gauss == 0.88)
	{
		regValue = 0x00;
		m_Scale = 0.73;
	}
	else if(gauss == 1.3)
	{
		regValue = 0x01;
		m_Scale = 0.92;
	}
	else if(gauss == 1.9)
	{
		regValue = 0x02;
		m_Scale = 1.22;
	}
	else if(gauss == 2.5)
	{
		regValue = 0x03;
		m_Scale = 1.52;
	}
	else if(gauss == 4.0)
	{
		regValue = 0x04;
		m_Scale = 2.27;
	}
	else if(gauss == 4.7)
	{
		regValue = 0x05;
		m_Scale = 2.56;
	}
	else if(gauss == 5.6)
	{
		regValue = 0x06;
		m_Scale = 3.03;
	}
	else if(gauss == 8.1)
	{
		regValue = 0x07;
		m_Scale = 4.35;
	}
	else
		return ErrorCode_1_Num;
	
	// Setting is in the top 3 bits of the register.
	regValue = regValue << 5;
	MagnWrite(ConfigurationRegisterB, regValue);
}

int Daisy7::MagnSetMeasurementMode(uint8_t mode)
{
	MagnWrite(ModeRegister, mode);
}

void Daisy7::MagnWrite(int address, int data)
{
  Wire.beginTransmission(HMC5883L_ADDRESS);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t* Daisy7::MagnRead(int address, int length)
{
  Wire.beginTransmission(HMC5883L_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.beginTransmission(HMC5883L_ADDRESS);
  Wire.requestFrom(HMC5883L_ADDRESS, length);

  uint8_t buffer[length];
  if(Wire.available() == length)
  {
	  for(uint8_t i = 0; i < length; i++)
	  {
		  buffer[i] = Wire.read();
	  }
  }
  Wire.endTransmission();

  return buffer;
}

char* Daisy7::MagnGetErrorText(int errorCode)
{
	if(ErrorCode_1_Num == 1)
		return ErrorCode_1;
	
	return "Error not defined.";
}

/*****  BMP085 Temperature\Baramoter *****/

// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void Daisy7::BaroCalibration()
{
    _ac1 = bmp085ReadInt(0xAA);
    _ac2 = bmp085ReadInt(0xAC);
    _ac3 = bmp085ReadInt(0xAE);
    _ac4 = bmp085ReadInt(0xB0);
    _ac5 = bmp085ReadInt(0xB2);
    _ac6 = bmp085ReadInt(0xB4);
    _b1 = bmp085ReadInt(0xB6);
    _b2 = bmp085ReadInt(0xB8);
    _b5=0;
    _mb = bmp085ReadInt(0xBA);
    _mc = bmp085ReadInt(0xBC);
    _md = bmp085ReadInt(0xBE);
}

// Calculate temperature in deg C
float Daisy7::BaroGetTemperature(unsigned int ut){
    long x1, x2;
    
    x1 = (((long)ut - (long)_ac6)*(long)_ac5) >> 15;
    x2 = ((long)_mc << 11)/(x1 + _md);
    _b5 = x1 + x2;
    
    float temp = ((_b5 + 8)>>4);
    temp = temp /10 - 1.5;
    
    return temp;
}

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long Daisy7::BaroGetPressure(unsigned long up){
    long x1, x2, x3, b3, b6, p;
    unsigned long b4, b7;
    
    b6 = _b5 - 4000;
    // Calculate B3
    x1 = (_b2 * (b6 * b6)>>12)>>11;
    x2 = (_ac2 * b6)>>11;
    x3 = x1 + x2;
    b3 = (((((long)_ac1)*4 + x3)<<OSS) + 2)>>2;
    
    // Calculate B4
    x1 = (_ac3 * b6)>>13;
    x2 = (_b1 * ((b6 * b6)>>12))>>16;
    x3 = ((x1 + x2) + 2)>>2;
    b4 = (_ac4 * (unsigned long)(x3 + 32768))>>15;
    
    b7 = ((unsigned long)(up - b3) * (50000>>OSS));
    if (b7 < 0x80000000)
        p = (b7<<1)/b4;
    else
        p = (b7/b4)<<1;
    
    x1 = (p>>8) * (p>>8);
    x1 = (x1 * 3038)>>16;
    x2 = (-7357 * p)>>16;
    p += (x1 + x2 + 3791)>>4;
    
    long temp = p;
    return temp;
}

// Read 1 uint8_t from the BMP085 at 'address'
char Daisy7::bmp085Read(unsigned char address)
{
    unsigned char data;
    
    Wire.beginTransmission(BMP085_ADDRESS);
    Wire.write(address);
    Wire.endTransmission();
    
    Wire.requestFrom(BMP085_ADDRESS, 1);
    while(!Wire.available())
        ;
    
    return Wire.read();
}

// Read 2 uint8_ts from the BMP085
// First uint8_t will be from 'address'
// Second uint8_t will be from 'address'+1
int Daisy7::bmp085ReadInt(unsigned char address)
{
    unsigned char msb, lsb;
    
    Wire.beginTransmission(BMP085_ADDRESS);
    Wire.write(address);
    Wire.endTransmission();
    
    Wire.requestFrom(BMP085_ADDRESS, 2);
    while(Wire.available()<2)
        ;
    msb = Wire.read();
    lsb = Wire.read();
    
    return (int) msb<<8 | lsb;
}

// Read the uncompensated temperature value
unsigned int Daisy7::bmp085ReadUT(){
    unsigned int ut;
    
    // Write 0x2E into Register 0xF4
    // This requests a temperature reading
    Wire.beginTransmission(BMP085_ADDRESS);
    Wire.write(0xF4);
    Wire.write(0x2E);
    Wire.endTransmission();
    
    // Wait at least 4.5ms
    delay(5);
    
    // Read two uint8_ts from registers 0xF6 and 0xF7
    ut = bmp085ReadInt(0xF6);
    return ut;
}

// Read the uncompensated pressure value
unsigned long Daisy7::bmp085ReadUP(){
    
    unsigned char msb, lsb, xlsb;
    unsigned long up = 0;
    
    // Write 0x34+(OSS<<6) into register 0xF4
    // Request a pressure reading w/ oversampling setting
    Wire.beginTransmission(BMP085_ADDRESS);
    Wire.write(0xF4);
    Wire.write(0x34 + (OSS<<6));
    Wire.endTransmission();
    
    // Wait for conversion, delay time dependent on OSS
    delay(2 + (3<<OSS));
    
    // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
    msb = bmp085Read(0xF6);
    lsb = bmp085Read(0xF7);
    xlsb = bmp085Read(0xF8);
    
    up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
    
    return up;
}


float Daisy7::calcAltitude(float pressure){
    
    float A = pressure/101325;
    float B = 1/5.25588;
    float C = pow(A,B);
    C = 1 - C;
    C = C /0.0000225577;
    
    return C;
}

/*****  LIS331DLH Accelerometer *****/

void Daisy7::AccConfig() {

    Wire.beginTransmission(LIS331DLH_ADDRESS);
    Wire.write(0x21); // CTRL_REG2 (21h)
    Wire.write(B01000000);
    //SPI 4/3 wire
    //1=ReBoot - reset chip defaults
    //n/a
    //filter off/on
    //filter for freefall 2
    //filter for freefall 1
    //filter freq MSB
    //filter freq LSB - Hipass filter (at 400hz) 00=8hz, 01=4hz, 10=2hz, 11=1hz (lower by 4x if sample rate is 100hz)
    Wire.endTransmission();
    Wire.beginTransmission(LIS331DLH_ADDRESS);
    Wire.write(0x20); // CTRL_REG1 (20h)
    Wire.write(B01000111);
    //sample rate 100/400hz
    //power off/on
    //2g/8g
    //self test
    //self test
    //z enable
    //y enable
    //x enable
    Wire.endTransmission();
}

AccelerometerRaw Daisy7::Accelerometer() {
    
    AccelerometerRaw raw = AccelerometerRaw();
    acc_status=B00000000;
    Wire.beginTransmission(LIS331DLH_ADDRESS);
    Wire.write(STATUSREG);
    Wire.endTransmission();
    
    Wire.requestFrom(LIS331DLH_ADDRESS, 1);
    if(Wire.available())
    {
        acc_status = Wire.read();
    }
    Wire.beginTransmission(LIS331DLH_ADDRESS);
    Wire.write(OUTXH);
    Wire.endTransmission();
    
    // X AXIS
    Wire.beginTransmission(LIS331DLH_ADDRESS);
    Wire.write(OUTXH);
    Wire.endTransmission();
    
    Wire.requestFrom(LIS331DLH_ADDRESS, 1);
    if(Wire.available())
    {
        raw.XAxis = Wire.read();
    }

    // Y AXIS
    Wire.beginTransmission(LIS331DLH_ADDRESS);
    Wire.write(OUTYH);
    Wire.endTransmission();
    
    Wire.requestFrom(LIS331DLH_ADDRESS, 1);
    if(Wire.available())
    {
        raw.YAxis = Wire.read();
    }
    
    // Z AXIS
    Wire.beginTransmission(LIS331DLH_ADDRESS);
    Wire.write(OUTZH);
    Wire.endTransmission();
    
    Wire.requestFrom(LIS331DLH_ADDRESS, 1);
    if(Wire.available())
    {
        raw.ZAxis = Wire.read();
    }
    
    return raw;

}


/*****  L3G4200D Gyroscope *****/

// Turns on the L3G4200D's gyro and places it in normal mode.
void Daisy7::GyroEnableDefault(void)
{
	// 0x0F = 0b00001111
	// Normal power mode, all axes enabled
	GyroWriteReg(L3G4200D_CTRL_REG1, 0x0F);
}

// Writes a gyro register
void Daisy7::GyroWriteReg(uint8_t reg, uint8_t value)
{
	Wire.beginTransmission(L3G4200D_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

// Reads a gyro register
uint8_t Daisy7::GyroReadReg(uint8_t reg)
{
	uint8_t value;
	
	Wire.beginTransmission(L3G4200D_ADDRESS);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(L3G4200D_ADDRESS, 1);
	value = Wire.read();
	Wire.endTransmission();
	
	return value;
}

// Reads the 3 gyro channels and stores them in vector g
GyroRaw Daisy7::GyroRead()
{
	Wire.beginTransmission(L3G4200D_ADDRESS);
	// assert the MSB of the address to get the gyro 
	// to do slave-transmit subaddress updating.
	Wire.write(L3G4200D_OUT_X_L | (1 << 7)); 
	Wire.endTransmission();
	Wire.requestFrom(L3G4200D_ADDRESS, 6);
    
	while (Wire.available() < 6){ }
	
	uint8_t xla = Wire.read();
	uint8_t xha = Wire.read();
	uint8_t yla = Wire.read();
	uint8_t yha = Wire.read();
	uint8_t zla = Wire.read();
	uint8_t zha = Wire.read();
    
	g.XAxis = xha << 8 | xla;
	g.YAxis = yha << 8 | yla;
	g.ZAxis = zha << 8 | zla;
    
    return g;
}

