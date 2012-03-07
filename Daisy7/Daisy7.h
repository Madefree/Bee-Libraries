
#ifndef Daisy7_h
#define Daisy7_h

#include <inttypes.h>
#include "Wire.h"

/* HMC5883 Magnetometer*/

#define HMC5883L_ADDRESS 0x1E
#define ConfigurationRegisterA 0x00
#define ConfigurationRegisterB 0x01
#define ModeRegister 0x02
#define DataRegisterBegin 0x03

#define Measurement_Continuous 0x00
#define Measurement_SingleShot 0x01
#define Measurement_Idle 0x03


#define ErrorCode_1 "Entered scale was not valid, valid gauss values are: 0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1"
#define ErrorCode_1_Num 1

/*****  BMP0085 Temperature\Baramoter *****/
#define BMP085_ADDRESS 0x77

const unsigned char OSS = 0;

struct MagnetometerScaled
{
	float XAxis;
	float YAxis;
	float ZAxis;
};

struct MagnetometerRaw
{
	int XAxis;
	int YAxis;
	int ZAxis;
};

/*****  LIS331DLH Accelerometer *****/
#define LIS331DLH_ADDRESS 0x18
#define OUTXH 0x29
#define OUTYH 0x2B
#define OUTZH 0x2D
#define STATUSREG 0x27

struct AccelerometerRaw
{
    int XAxis;
    int YAxis;
    int ZAxis;
};

/*** Daisy7 Class ***/

class Daisy7
{
public:
    Daisy7();
    
    /* HMC5883 Magnetometer*/
    MagnetometerRaw MagnReadRawAxis();
    MagnetometerScaled MagnReadScaledAxis();
    int MagnSetMeasurementMode(uint8_t mode);
    int MagnSetScale(float gauss);
    char* MagnGetErrorText(int errorCode);
    
    /*****  BMP0085 Temperature\Baramoter *****/
    void BaroCalibration();
    float BaroGetTemperature(unsigned int ut);
    long BaroGetPressure(unsigned long up);
    unsigned int bmp085ReadUT();
    unsigned long bmp085ReadUP();
    float calcAltitude(float pressure);
    
    /*****  LIS331DLH Accelerometer *****/
    void AccConfig();
    AccelerometerRaw Accelerometer();
    
protected:
    
    /* HMC5883 Magnetometer*/
    void MagnWrite(int address, int byte);
    uint8_t* MagnRead(int address, int length);
    
    /*****  BMP0085 Temperature\Baramoter *****/
    char bmp085Read(unsigned char address);
    int bmp085ReadInt(unsigned char address);
    
    
private:
    /* HMC5883 Magnetometer*/
    float m_Scale;
    
    /*****  BMP0085 Temperature\Baramoter *****/
    int _ac1;
    int _ac2;
    int _ac3;
    unsigned int _ac4;
    unsigned int _ac5;
    unsigned int _ac6;
    int _b1;
    int _b2;
    int _mb;
    int _mc;
    int _md;
    long _b5;
    
    /*****  LIS331DLH Accelerometer *****/
    
    unsigned char acc_status;
};
#endif