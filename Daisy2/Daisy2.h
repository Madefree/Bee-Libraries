#ifndef Daisy2_h
#define Daisy2_h

#include <WProgram.h>

#define A 0
#define B 1

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


class Daisy2 {
	public:
		Daisy2(int wing,int conf);
		void begin();
		void setSpeed(long speed);
		void direction(int dir);
		void invertDirection();
		void motorEN(int en);
		void step(int nstep);

	private:
		int _wing;
		int _conf;
		int _step;
		int _en;
		int _dir;
		unsigned long _speed;
		int Wing3(int pin);
		int Wing4(int pin);
};

#endif



	
