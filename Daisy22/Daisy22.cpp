#include "Daisy22.h"

#include <WProgram.h>
#include <inttypes.h>
#include "../Wire/Wire.h"


Daisy22::Daisy22(uint8_t address) {
	_address=address;
	_status=0x00;
}

void Daisy22::begin() {
	Wire.begin();
	Wire.beginTransmission(_address);
	Wire.send(_status);
	Wire.endTransmission();

}

void Daisy22::digitalWrite(uint8_t pin,uint8_t value) {
	if (pin >= 0 && pin <=7) {
		if(value == HIGH) 
			_status |= 1<<pin;
		else
			_status &= ~(1 << pin);
		Wire.beginTransmission(_address);
		Wire.send(_status);
		Wire.endTransmission();
	}	
}

void Daisy22::digitalWrite(uint8_t state) {		
		_status=state;
		Wire.beginTransmission(_address);
		Wire.send(_status);
		Wire.endTransmission();
}

uint8_t Daisy22::digitalRead(uint8_t pin) {
	uint8_t value;
	Wire.requestFrom(_address,(uint8_t)1);
	if (Wire.available()) {
		value= Wire.receive();
	}
	if (1<<pin & value) 
		return(HIGH);
	else
		return(LOW);
}	

uint8_t Daisy22::digitalRead(void) {
	uint8_t value;
	Wire.requestFrom(_address,(uint8_t)1);
	if (Wire.available()) {
		value= Wire.receive();
	}
	return(value);
}