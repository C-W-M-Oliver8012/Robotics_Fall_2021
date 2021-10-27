#ifndef RC
#define RC

#define PERIOD 30000
#define RC_PWM_MIN 990
#define RC_PWM_MAX 1980
#define POS_THRES 15
#define NEG_THRES -15

typedef struct Rc {
	int pin_AILE;
	int pin_ELEV;
	int pin_THRO;
	int pin_AUX5;
	int pin_AUX8;
	int pin_AUX7;

	int val_AILE;
	int val_ELEV;
	int val_THRO;
	int val_AUX5;
	int val_AUX8;
	int val_AUX7;
} Rc;

void rc_init(
	Rc *rc,
	const int pin_AILE,
	const int pin_ELEV,
	const int pin_THRO,
	const int pin_AUX5,
	const int pin_AUX6,
	const int pin_AUX7
);

void rc_io_init(Rc *rc);
void rc_get_AILE(Rc *rc);
void rc_get_ELEV(Rc *rc);
void rc_get_THRO(Rc *rc);
void rc_get_AUX5(Rc *rc);
void rc_get_AUX6(Rc *rc);
void rc_get_AUX7(Rc *rc);
void rc_print(Rc *rc);

#endif
