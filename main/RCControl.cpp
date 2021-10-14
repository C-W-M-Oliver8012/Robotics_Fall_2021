#include "RCControl.h"

RCControl::RCControl(
	unsigned char _pinTHRO,
	unsigned char _pinAILE,
	unsigned char _pinELEV,
	unsigned char _pinRUDD,
	unsigned char _pinGEAR,
	unsigned char _pinAUX1,
	unsigned char _pinAUX2
) {
		pinTHRO = _pinTHRO;
		pinAILE = _pinAILE;
		pinELEV = _pinELEV;
		pinRUDD = _pinRUDD;
		pinGEAR = _pinGEAR;
		pinAUX1 = _pinAUX1;
		pinAUX2 = _pinAUX2;

		pinMode(pinTHRO, INPUT);
		pinMode(pinAILE, INPUT);
		pinMode(pinELEV, INPUT);
		pinMode(pinRUDD, INPUT);
		pinMode(pinGEAR, INPUT);
		pinMode(pinAUX1, INPUT);
		pinMode(pinAUX2, INPUT);
}

int RCControl::get_THRO(void) {
	int val_THRO_RAW = pulseIn(pinTHRO, HIGH, PERIOD);
	if (val_THRO_RAW <= RC_PWM_MIN || val_THRO_RAW >= RC_PWM_MAX) {
		if (val_THRO_RAW <= RC_PWM_MIN)
			val_THRO_RAW = RC_PWM_MIN;
		else if (val_THRO_RAW >= RC_PWM_MAX)
			val_THRO_RAW = RC_PWM_MAX;
	}
	val_THRO = map(val_THRO_RAW, RC_PWM_MIN, RC_PWM_MAX, 0, 100);
	return val_THRO;
}

int RCControl::get_AILE(void) {
	int val_AILE_RAW = pulseIn(pinAILE, HIGH, PERIOD);
	if (val_AILE_RAW <= RC_PWM_MIN || val_AILE_RAW >= RC_PWM_MAX) {
		if (val_AILE_RAW <= RC_PWM_MIN)
			val_AILE_RAW = RC_PWM_MIN;
		else if (val_AILE_RAW >= RC_PWM_MAX)
			val_AILE_RAW = RC_PWM_MAX;
	}
	val_AILE = map(val_AILE_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
	return val_AILE;
}

int RCControl::get_ELEV(void) {
	int val_ELEV_RAW = pulseIn(pinELEV, HIGH, PERIOD);
	if (val_ELEV_RAW <= RC_PWM_MIN || val_ELEV_RAW >= RC_PWM_MAX) {
		if (val_ELEV_RAW <= RC_PWM_MIN)
			val_ELEV_RAW = RC_PWM_MIN;
		else if (val_ELEV_RAW >= RC_PWM_MAX)
			val_ELEV_RAW = RC_PWM_MAX;
	}
	val_ELEV = map(val_ELEV_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
	return val_ELEV;
}

int RCControl::get_RUDD(void) {
	int val_RUDD_RAW = pulseIn(pinRUDD, HIGH, PERIOD);
	if (val_RUDD_RAW <= RC_PWM_MIN || val_RUDD_RAW >= RC_PWM_MAX) {
		if (val_RUDD_RAW <= RC_PWM_MIN)
			val_RUDD_RAW = RC_PWM_MIN;
		else if (val_RUDD_RAW >= RC_PWM_MAX)
			val_RUDD_RAW = RC_PWM_MAX;
	}
	val_RUDD = map(val_RUDD_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
	return val_RUDD;
}

int RCControl::get_GEAR(void) {
	int val_GEAR_RAW = pulseIn(pinGEAR, HIGH);
	if (val_GEAR_RAW < 1300) {
		val_GEAR = -100;
	}
	else if (val_GEAR_RAW > 1700) {
		val_GEAR = 100;
	}
	return val_GEAR;
}

int RCControl::get_AUX1(void) {
	int val_AUX1_RAW = pulseIn(pinAUX1, HIGH);
	if (val_AUX1_RAW < 1300) {
		val_AUX1 = -100;
	}
	else if (val_AUX1_RAW > 1300 && val_AUX1_RAW < 1700) {
		val_AUX1 = 0;
	}
	else if (val_AUX1_RAW > 1700) {
		val_AUX1 = 100;
	}
	return val_AUX1;
}

int RCControl::get_AUX2(void) {
	int val_AUX2_RAW = pulseIn(pinAUX2, HIGH, PERIOD);
	if (val_AUX2_RAW <= RC_PWM_MIN || val_AUX2_RAW >= RC_PWM_MAX) {
		if (val_AUX2_RAW <= RC_PWM_MIN)
			val_AUX2_RAW = RC_PWM_MIN;
		else if (val_AUX2_RAW >= RC_PWM_MAX)
			val_AUX2_RAW = RC_PWM_MAX;
	}
	val_AUX2 = map(val_AUX2_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
	return val_AUX2;
}

void RCControl::print_manual(void) {
	Serial.print(val_THRO);
	Serial.print(" ,");
	Serial.print(val_AILE);
	Serial.print(" ,");
	Serial.print(val_ELEV);
	Serial.print(" ,");
	Serial.print(val_RUDD);
	Serial.print(" ,");
	Serial.print(val_GEAR);
	Serial.print(" ,");
	Serial.print(val_AUX1);
	Serial.print(" ,");
	Serial.println(val_AUX2);
}
