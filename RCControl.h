#ifndef RC_CONTROL
#define RC_CONTROL

#include <Arduino.h>

#define PERIOD		3000
#define RC_PWM_MIN		1148
#define RC_PWM_MAX		1900

#define POS_THRES 20
#define NEG_THRES -20

class RCControl {
	public:
		RCControl(
			unsigned char _pinTHRO,
			unsigned char _pinAILE,
			unsigned char _pinELEV,
			unsigned char _pinRUDD,
			unsigned char _pinGEAR,
			unsigned char _pinAUX1,
			unsigned char _pinAUX2
		);

		int get_THRO(void);
		int get_AILE(void);
		int get_ELEV(void);
		int get_RUDD(void);
		int get_GEAR(void);
		int get_AUX1(void);
		int get_AUX2(void);

		void print_manual(void);

	private:
		unsigned char pinTHRO;
		unsigned char pinAILE;
		unsigned char pinELEV;
		unsigned char pinRUDD;
		unsigned char pinGEAR;
		unsigned char pinAUX1;
		unsigned char pinAUX2;

		int val_THRO;
		int val_AILE;
		int val_ELEV;
		int val_RUDD;
		int val_GEAR;
		int val_AUX1;
		int val_AUX2;

		RCControl();
};

#endif
