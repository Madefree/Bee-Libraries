#include "Daisy5.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


Daisy5::Daisy5(int wing) {
	_wing=wing;
	
}

void Daisy5::begin(void) {
	for(int i=2; i<9; i++) {
		if(_wing == W3)
			pinMode(Wing3(i),INPUT);
		else if(_wing == W4 && (i!=7 || i!=8))
			pinMode(Wing4(i),INPUT);
	}
}

int Daisy5::readButton(int pin) {
	if(pin >=1 && pin <= 7) {
		if(_wing==W3)
			return digitalRead(Wing3(pin+1));
		else if(_wing == W4) {
			if(pin==6){
				int value=analogRead(4);
				if(value>=755)
					return HIGH;
				else
					return LOW;
			}
			else if(pin==7) {
				int value=analogRead(5);
				if(value>=755)
					return HIGH;
				else
					return LOW;
			}
			else
				return digitalRead(Wing4(pin+1));
		}
	}
}


int Daisy5::Wing3(int pin) {
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

int Daisy5::Wing4(int pin) {
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
