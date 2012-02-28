#include "Daisy11.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


Daisy11::Daisy11(int wing) {
	_wing=wing;
	
}

void Daisy11::begin(void) {
	for (int i=2; i<9; i++) {
		if(_wing == W3)
			pinMode(Wing3(i),OUTPUT);
		else if (_wing == W4)
			pinMode(Wing4(i),OUTPUT);
	}
}

void Daisy11::ledOn(int pin) {
	if (_wing==W3) 
		digitalWrite(Wing3(pin+1),HIGH);
	else if (_wing == W4)
		digitalWrite(Wing4(pin+1),HIGH);
}

void Daisy11::ledSwitch(int pin) {
	if (_wing==W3)
		digitalWrite(Wing3(pin+1),!digitalRead(Wing3(pin+1)));
	else if (_wing == W4)
		digitalWrite(Wing4(pin+1),!digitalRead(Wing4(pin+1)));
}

void Daisy11::ledOff(int pin) {
	if (_wing==W3)
		digitalWrite(Wing3(pin+1),LOW);
	else if (_wing == W4)
		digitalWrite(Wing4(pin+1),LOW);	
}

int Daisy11::Wing3(int pin) {
	switch (pin) {
		case 2:
			return(W3_2);
		case 3:
			return(W3_3);
		case 4:
			return(W3_4);
		case 5:
			return(W3_5);
		case 6:
			return(W3_6);
		case 7:
			return(W3_7);
		case 8:
			return(W3_8);
	}
}

int Daisy11::Wing4(int pin) {
	switch (pin) {
		case 2:
			return(W4_2);
		case 3:
			return(W4_3);
		case 4:
			return(W4_4);
		case 5:
			return(W4_5);
		case 6:
			return(W4_6);
		case 7:
			return(W4_7);
		case 8:
			return(W4_8);
	}
}
