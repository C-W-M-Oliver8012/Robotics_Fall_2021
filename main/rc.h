#ifndef RC
#define RC

#define PERIOD 30000
#define RC_PWM_MIN 990
#define RC_PWM_MAX 1980
#define POS_THRES 15
#define NEG_THRES -15

typedef struct Rc {
	int pinAILE;
	int pinELEV;
	int pinTHRO;
	int val_AILE;
	int val_ELEV;
	int val_THRO;
} Rc;

void rc_init(
	Rc *rc,
	const int _pinAILE,
	const int _pinELEV,
	const int _pinTHRO
);

void rc_io_init(Rc *rc);
void rc_get_AILE(Rc *rc);
void rc_get_ELEV(Rc *rc);
void rc_get_THRO(Rc *rc);
void rc_print(Rc *rc);

#endif
