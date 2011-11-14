#include "Daisy2.h"

#include <WProgram.h>

Daisy2::Daisy2(int wing,int conf) {
	_wing=wing;
	_conf=conf;
	_step=0;
	_en=0;
	_dir=0;
	_speed=0;
}

void Daisy2::begin() {
	if(_wing == W3) {
		if(_conf==A) {
			_step=Wing3(6);
			_en=Wing3(2);
			_dir=Wing3(4);
		}
		else if(_conf==B) {
			_step=Wing3(7);
			_en=Wing3(3);
			_dir=Wing3(5);
		}
	}
	else if(_wing==W4) {
		if(_conf==A) {
			_step=Wing4(6);
			_en=Wing4(2);
			_dir=Wing4(4);
		}
	}
	pinMode(_step,OUTPUT);
	pinMode(_en,OUTPUT);
	pinMode(_dir,OUTPUT);
}

void Daisy2::setSpeed(long speed)
{
	_speed = speed;
}

void Daisy2::direction(int dir) {
	if(dir)
		digitalWrite(_dir,LOW);
	else
		digitalWrite(_dir,HIGH);
}

void Daisy2::invertDirection(void) {
	digitalWrite(_dir,!digitalRead(_dir));
}

void Daisy2::motorEN(int en) {
	if(en)
		digitalWrite(_en,LOW);
	else
		digitalWrite(_en,HIGH);
}

void Daisy2::step(int nstep) {
	motorEN(1);
	for(int i=0; i<nstep; i++) {
		digitalWrite(_step,HIGH);
		delayMicroseconds(_speed);
		digitalWrite(_step,LOW);
		delayMicroseconds(_speed);
	}
	motorEN(0);
}

int Daisy2::Wing3(int pin) {
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

int Daisy2::Wing4(int pin) {
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
	}
}
