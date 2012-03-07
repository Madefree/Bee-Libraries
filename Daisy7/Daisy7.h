/*
 * Daniele Sdei, Marco Antonini 2012 Madefree Electronics (www.madefree.eu)
 *
 * HMC5883L section is based on code by Love Electronics (loveelectronics.co.uk)
 * BMP085 section is based on code by Jim Lindblom
 * 
 */

#ifndef Daisy7_h
#define Daisy7_h

#include "inttypes.h"
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

/*****  BMP085 Temperature\Baramoter *****/
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


/*****  L3G4200D Gyroscope *****/
#define L3G4200D_ADDRESS       0x68
#define L3G4200D_WHO_AM_I      0x0F

#define L3G4200D_CTRL_REG1     0x20
#define L3G4200D_CTRL_REG2     0x21
#define L3G4200D_CTRL_REG3     0x22
#define L3G4200D_CTRL_REG4     0x23
#define L3G4200D_CTRL_REG5     0x24
#define L3G4200D_REFERENCE     0x25
#define L3G4200D_OUT_TEMP      0x26
#define L3G4200D_STATUS_REG    0x27

#define L3G4200D_OUT_X_L       0x28
#define L3G4200D_OUT_X_H       0x29
#define L3G4200D_OUT_Y_L       0x2A
#define L3G4200D_OUT_Y_H       0x2B
#define L3G4200D_OUT_Z_L       0x2C
#define L3G4200D_OUT_Z_H       0x2D

#define L3G4200D_FIFO_CTRL_REG 0x2E
#define L3G4200D_FIFO_SRC_REG  0x2F

#define L3G4200D_INT1_CFG      0x30
#define L3G4200D_INT1_SRC      0x31
#define L3G4200D_INT1_THS_XH   0x32
#define L3G4200D_INT1_THS_XL   0x33
#define L3G4200D_INT1_THS_YH   0x34
#define L3G4200D_INT1_THS_YL   0x35
#define L3G4200D_INT1_THS_ZH   0x36
#define L3G4200D_INT1_THS_ZL   0x37
#define L3G4200D_INT1_DURATION 0x38

struct GyroRaw
{
	float XAxis;
	float YAxis;
	float ZAxis;
};

/*** Daisy7 Class ***/

class Daisy7
{
public:
    Daisy7();
    void begin();
    
    /* HMC5883 Magnetometer*/
    MagnetometerRaw MagnReadRawAxis();
    MagnetometerScaled MagnReadScaledAxis();
    int MagnSetMeasurementMode(uint8_t mode);
    int MagnSetScale(float gauss);
    char* MagnGetErrorText(int errorCode);
    
    /*****  BMP085 Temperature\Baramoter *****/
    void BaroCalibration();
    float BaroGetTemperature(unsigned int ut);
    long BaroGetPressure(unsigned long up);
    unsigned int bmp085ReadUT();
    unsigned long bmp085ReadUP();
    float calcAltitude(float pressure);
    
    /*****  LIS331DLH Accelerometer *****/
    void AccConfig();
    AccelerometerRaw Accelerometer();
    
    /*****  L3G4200D Gyroscope *****/
    void GyroEnableDefault(void);
    void GyroWriteReg(uint8_t reg, uint8_t value);
    uint8_t GyroReadReg(uint8_t reg);
    GyroRaw GyroRead(void);
    
    
protected:
    
    /* HMC5883 Magnetometer*/
    void MagnWrite(int address, int uint8_t);
    uint8_t* MagnRead(int address, int length);
    
    /*****  BMP085 Temperature\Baramoter *****/
    char bmp085Read(unsigned char address);
    int bmp085ReadInt(unsigned char address);
    
    
private:
    /* HMC5883 Magnetometer*/
    float m_Scale;
    
    /*****  BMP085 Temperature\Baramoter *****/
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
    
    /*****  L3G4200D Gyroscope *****/
    GyroRaw g;

};
#endif