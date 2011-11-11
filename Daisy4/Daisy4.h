#ifndef Daisy4_h
#define Daisy4_h

#include <WProgram.h>


#define W2 2
#define W3 3
#define W4 4

#define W2_5 14
#define W2_6 15
#define W2_7 16
#define W2_8 17

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

#define DIP1 2
#define DIP2 3
#define DIP3 4
#define DIP4 5
#define DIP5 6
#define DIP6 7
#define DIP7 8


class Daisy4 {
	public:
		Daisy4(int wing, int dipswitch);
		void begin();
		int readState(void);
		void relayOn(void);
		void relayOff(void);

	private:
		int _wing;
		int _dipswitch;
		int Wing2(int pin);
		int Wing3(int pin);
		int Wing4(int pin);
};

#endif



	
