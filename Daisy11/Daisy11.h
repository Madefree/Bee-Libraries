#ifndef Daisy11_h
#define Daisy11_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#define W3 3
#define W4 4

#define W3_2 11
#define W3_3 12
#define W3_4 13
#define W3_5 10
#define W3_6 9
#define W3_7 5
#define W3_8 6

#define W4_2 8
#define W4_3 7
#define W4_4 2
#define W4_5 3
#define W4_6 4
#define W4_7 18
#define W4_8 19

#define P1 1
#define P2 2
#define P3 3
#define P4 4
#define P5 5
#define P6 6
#define P7 7

class Daisy11 {
	public:
		Daisy11(int wing);
		void begin(void);
		void ledOn(int pin);
		void ledOff(int pin);
		void ledSwitch(int pin);

	private:
		int _wing;
		int Wing3(int pin);
		int Wing4(int pin);
};

#endif
