#ifndef Daisy22_h
#define Daisy22_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>
#include "../Wire/Wire.h"

#define P0 0
#define P1 1
#define P2 2
#define P3 3
#define P4 4
#define P5 5
#define P6 6
#define P7 7

class Daisy22 {
public:
	Daisy22(uint8_t address);
	void begin(void);
	void digitalWrite(uint8_t pin,uint8_t state);
	void digitalWrite(uint8_t state);
	uint8_t digitalRead(uint8_t pin);
	uint8_t digitalRead(void);
		
private:
	uint8_t _address;
	uint8_t _status;
	
};

#endif



	
