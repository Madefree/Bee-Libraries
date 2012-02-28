#include "Daisy4.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


Daisy4::Daisy4(int wing, int dipswitch) {
	_wing=wing;
	_dipswitch=dipswitch;

}

void Daisy4::begin() {
	if(_wing == W2) {
		if (_dipswitch >= 5 && _dipswitch <= 8)
			pinMode(Wing2(_dipswitch),OUTPUT);
	}
	else if(_wing == W3) {
		if (_dipswitch >= 2 && _dipswitch <= 8)
			pinMode(Wing3(_dipswitch),OUTPUT);
	}
	else if(_wing == W4) {
		if (_dipswitch >= 2 && _dipswitch <= 8)
			pinMode(Wing4(_dipswitch),OUTPUT);
	}
}

int Daisy4::readState(void) {
	switch (_wing) {
		case W2:
			return digitalRead(Wing2(_dipswitch));
		case W3:
			return digitalRead(Wing3(_dipswitch));
		case W4:
			return digitalRead(Wing4(_dipswitch));
	}
}

void Daisy4::relayOn(void) {
	switch (_wing) {
		case W2:
			digitalWrite(Wing2(_dipswitch), HIGH);
		case W3:
			digitalWrite(Wing3(_dipswitch), HIGH);
		case W4:
			digitalWrite(Wing4(_dipswitch), HIGH);
	}
}

void Daisy4::relayOff(void) {
	switch (_wing) {
		case W2:
			digitalWrite(Wing2(_dipswitch), LOW);
		case W3:
			digitalWrite(Wing3(_dipswitch), LOW);
		case W4:
			digitalWrite(Wing4(_dipswitch), LOW);
	}
}

int Daisy4::Wing2(int pin) {
	switch (pin) {
		case 5:
			return(W2_5);
		case 6:
			return(W2_6);
		case 7:
			return(W2_7);
		case 8:
			return(W2_8);
	}
}

int Daisy4::Wing3(int pin) {
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

int Daisy4::Wing4(int pin) {
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
