#include "Daisy22.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>
#include "../Wire/Wire.h"


Daisy22::Daisy22(uint8_t address) {
	_address=address;
	_status=0x00;
}

void Daisy22::begin() {
	Wire.begin();
	Wire.beginTransmission(_address);
    
    #if defined(ARDUINO) && ARDUINO >= 100
    Wire.write(_status);
    #else
	Wire.send(_status);
    #endif
    
	Wire.endTransmission();

}

void Daisy22::digitalWrite(uint8_t pin,uint8_t value) {
	if (pin >= 0 && pin <=7) {
		if(value == HIGH) 
			_status |= 1<<pin;
		else
			_status &= ~(1 << pin);
		Wire.beginTransmission(_address);
        
        #if defined(ARDUINO) && ARDUINO >= 100
        Wire.write(_status);
        #else
        Wire.send(_status);
        #endif
        
		Wire.endTransmission();
	}	
}

void Daisy22::digitalWrite(uint8_t state) {		
		_status=state;
		Wire.beginTransmission(_address);
        
        #if defined(ARDUINO) && ARDUINO >= 100
        Wire.write(_status);
        #else
        Wire.send(_status);
        #endif
		
		Wire.endTransmission();
}

uint8_t Daisy22::digitalRead(uint8_t pin) {
	uint8_t value;
	Wire.requestFrom(_address,(uint8_t)1);
	if (Wire.available()) {
        #if defined(ARDUINO) && ARDUINO >= 100
        value= Wire.read();
        #else
		value= Wire.receive();
        #endif
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
        #if defined(ARDUINO) && ARDUINO >= 100
        value= Wire.read();
        #else
		value= Wire.receive();
        #endif
	}
	return(value);
}