#include "rc.h"
#include "wc.h"

#define SERIAL_NUM 115200

#define PIN_AILE 39
#define PIN_ELEV 40
#define PIN_THRO 41

Rc rc;
Wc wc;

void setup(void) {
	rc_init(&rc, PIN_AILE, PIN_ELEV, PIN_THRO);
	wc_init(&wc, 0);

	Serial.begin(SERIAL_NUM);
	rc_io_init(&rc);
	wc_io_init(&wc);
}

void loop(void) {
	// get rc values
	rc_get_AILE(&rc);
	rc_get_ELEV(&rc);
	rc_get_THRO(&rc);

	// print rc values
	rc_print(&rc);

	// set wc speed
	if (rc.val_THRO >= POS_THRES) {
		wc.motor_pwd = map(rc.val_THRO, POS_THRES, 100, 1, 255);
	} else {
		wc.motor_pwd = 0;
		wc_stop(&wc);
	}

	// set wc direction
	if (rc.val_ELEV >= POS_THRES) {
		wc_forward(&wc);
	} else if (rc.val_ELEV <= NEG_THRES) {
		wc_reverse(&wc);
	} else if (rc.val_AILE <= NEG_THRES) {
		wc_turn_left(&wc);
	} else if (rc.val_AILE >= POS_THRES) {
		wc_turn_right(&wc);
	} else {
		wc_stop(&wc);
	}
}
