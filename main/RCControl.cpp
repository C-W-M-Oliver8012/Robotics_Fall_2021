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
	this->pinTHRO = _pinTHRO;
	this->pinAILE = _pinAILE;
	this->pinELEV = _pinELEV;
	this->pinRUDD = _pinRUDD;
	this->pinGEAR = _pinGEAR;
	this->pinAUX1 = _pinAUX1;
	this->pinAUX2 = _pinAUX2;

	pinMode(this->pinTHRO, INPUT);
	pinMode(this->pinAILE, INPUT);
	pinMode(this->pinELEV, INPUT);
	pinMode(this->pinRUDD, INPUT);
	pinMode(this->pinGEAR, INPUT);
	pinMode(this->pinAUX1, INPUT);
	pinMode(this->pinAUX2, INPUT);
}

int RCControl::get_THRO(void) {
	int const val_THRO_RAW = pulseIn(this->pinTHRO, HIGH, PERIOD);
	if (val_THRO_RAW <= RC_PWM_MIN || val_THRO_RAW >= RC_PWM_MAX) {
		if (val_THRO_RAW <= RC_PWM_MIN)
			val_THRO_RAW = RC_PWM_MIN;
		else if (val_THRO_RAW >= RC_PWM_MAX)
			val_THRO_RAW = RC_PWM_MAX;
	}
	this->val_THRO = map(val_THRO_RAW, RC_PWM_MIN, RC_PWM_MAX, 0, 100);
	return this->val_THRO;
}

int RCControl::get_AILE(void) {
	int const val_AILE_RAW = pulseIn(this->pinAILE, HIGH, PERIOD);
	if (val_AILE_RAW <= RC_PWM_MIN || val_AILE_RAW >= RC_PWM_MAX) {
		if (val_AILE_RAW <= RC_PWM_MIN)
			val_AILE_RAW = RC_PWM_MIN;
		else if (val_AILE_RAW >= RC_PWM_MAX)
			val_AILE_RAW = RC_PWM_MAX;
	}
	this->val_AILE = map(val_AILE_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
	return this->val_AILE;
}

int RCControl::get_ELEV(void) {
	int const val_ELEV_RAW = pulseIn(this->pinELEV, HIGH, PERIOD);
	if (val_ELEV_RAW <= RC_PWM_MIN || val_ELEV_RAW >= RC_PWM_MAX) {
		if (val_ELEV_RAW <= RC_PWM_MIN)
			val_ELEV_RAW = RC_PWM_MIN;
		else if (val_ELEV_RAW >= RC_PWM_MAX)
			val_ELEV_RAW = RC_PWM_MAX;
	}
	this->val_ELEV = map(val_ELEV_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
	return this->val_ELEV;
}

int RCControl::get_RUDD(void) {
	int const val_RUDD_RAW = pulseIn(this->pinRUDD, HIGH, PERIOD);
	if (val_RUDD_RAW <= RC_PWM_MIN || val_RUDD_RAW >= RC_PWM_MAX) {
		if (val_RUDD_RAW <= RC_PWM_MIN)
			val_RUDD_RAW = RC_PWM_MIN;
		else if (val_RUDD_RAW >= RC_PWM_MAX)
			val_RUDD_RAW = RC_PWM_MAX;
	}
	this->val_RUDD = map(val_RUDD_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
	return this->val_RUDD;
}

int RCControl::get_GEAR(void) {
	int const val_GEAR_RAW = pulseIn(this->pinGEAR, HIGH);
	if (val_GEAR_RAW < 1300) {
		this->val_GEAR = -100;
	} else if (val_GEAR_RAW > 1700) {
		this->val_GEAR = 100;
	}
	return this->val_GEAR;
}

int RCControl::get_AUX1(void) {
	int const val_AUX1_RAW = pulseIn(this->pinAUX1, HIGH);
	if (val_AUX1_RAW < 1300) {
		this->val_AUX1 = -100;
	}
	else if (val_AUX1_RAW > 1300 && val_AUX1_RAW < 1700) {
		this->val_AUX1 = 0;
	}
	else if (val_AUX1_RAW > 1700) {
		this->val_AUX1 = 100;
	}
	return this->val_AUX1;
}

int RCControl::get_AUX2(void) {
	int const val_AUX2_RAW = pulseIn(this->pinAUX2, HIGH, PERIOD);
	if (val_AUX2_RAW <= RC_PWM_MIN || val_AUX2_RAW >= RC_PWM_MAX) {
		if (val_AUX2_RAW <= RC_PWM_MIN)
			val_AUX2_RAW = RC_PWM_MIN;
		else if (val_AUX2_RAW >= RC_PWM_MAX)
			val_AUX2_RAW = RC_PWM_MAX;
	}
	this->val_AUX2 = map(val_AUX2_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
	return this->val_AUX2;
}

void RCControl::print_manual(void) {
	Serial.print(this->val_THRO);
	Serial.print(" ,");
	Serial.print(this->val_AILE);
	Serial.print(" ,");
	Serial.print(this->val_ELEV);
	Serial.print(" ,");
	Serial.print(this->val_RUDD);
	Serial.print(" ,");
	Serial.print(this->val_GEAR);
	Serial.print(" ,");
	Serial.print(this->val_AUX1);
	Serial.print(" ,");
	Serial.println(this->val_AUX2);
}
