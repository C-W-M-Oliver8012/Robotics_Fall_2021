#include "rc.h"
#include "wc.h"

#define SERIAL_NUM 115200

#define PIN_AILE 39
#define PIN_ELEV 40
#define PIN_THRO 41
#define PIN_AUX5 42
#define PIN_AUX8 43
#define PIN_AUX7 44

Rc rc;
Wc wc;

void setup(void) {
	rc_init(&rc, PIN_AILE, PIN_ELEV, PIN_THRO, PIN_AUX5, PIN_AUX8, PIN_AUX7);
	wc_init(&wc, 0);

	Serial1.begin(SERIAL_NUM);
	rc_io_init(&rc);
	wc_io_init(&wc);
}

void loop(void) {
	// get rc values
	rc_get_AILE(&rc);
	rc_get_ELEV(&rc);
	rc_get_THRO(&rc);
	rc_get_AUX5(&rc);
	rc_get_AUX8(&rc);
	rc_get_AUX7(&rc);

	// print rc values
	rc_print(&rc);

	// set is_automatic
	if (rc.val_AUX8 == 100) {
		wc.is_automatic = true;
		wc.motor_pwd = AUTOMATIC_SPEED;
	} else {
		wc.is_automatic = false;
	}

	if (wc.is_automatic == false) {
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

		// move stepper
		if (rc.val_AUX5 == 100 && rc.val_AUX7 == 100) {
			Serial1.write(1);
			Serial.println("One");
		} else if (rc.val_AUX5 == 100 && rc.val_AUX7 == 0) {
			Serial1.write(2);
			Serial.println("Two");
		} else if (rc.val_AUX5 == 100 && rc.val_AUX7 == -100) {
			Serial1.write(3);
			Serial.println("Three");
		} else if (rc.val_AUX5 == 0 && rc.val_AUX7 == 100) {
			Serial1.write(4);
			Serial.println("Four");
		} else if (rc.val_AUX5 == 0 && rc.val_AUX7 == 0) {
			Serial1.write(5);
			Serial.println("Five");
		} else if (rc.val_AUX5 == 0 && rc.val_AUX7 == -100) {
			Serial1.write(6);
			Serial.println("Six");
		} else if (rc.val_AUX5 == -100 && rc.val_AUX7 == 100) {
			Serial1.write(7);
			Serial.println("Seven");
		} else if (rc.val_AUX5 == -100 && rc.val_AUX7 == 0) {
			Serial1.write(8);
			Serial.println("Eight");
		} else if (rc.val_AUX5 == -100 && rc.val_AUX7 == -100) {
			Serial1.write(9);
			Serial.println("Nine");
		}
	} else {
		wc_auto_avoidance(&wc);
	}
}
