void rc_init(
	Rc *rc,
	const int _pinAILE,
	const int _pinELEV,
	const int _pinTHRO
) {
	rc->pinAILE = _pinAILE;
	rc->pinELEV = _pinELEV;
	rc->pinTHRO = _pinTHRO;

	rc->val_AILE = 0;
	rc->val_ELEV = 0;
	rc->val_THRO = 0;
}

void rc_io_init(Rc *rc) {
	pinMode(rc->pinAILE, INPUT);
	pinMode(rc->pinELEV, INPUT);
	pinMode(rc->pinTHRO, INPUT);
}

void rc_get_AILE(Rc *rc) {
	int val_AILE_RAW = pulseIn(rc->pinAILE, HIGH, PERIOD);
	if (val_AILE_RAW <= RC_PWM_MIN || val_AILE_RAW >= RC_PWM_MAX) {
		if (val_AILE_RAW <= RC_PWM_MIN)
			val_AILE_RAW = RC_PWM_MIN;
		else if (val_AILE_RAW >= RC_PWM_MAX)
			val_AILE_RAW = RC_PWM_MAX;
	}
	rc->val_AILE = map(val_AILE_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
}

void rc_get_ELEV(Rc *rc) {
	int val_ELEV_RAW = pulseIn(rc->pinELEV, HIGH, PERIOD);
	if (val_ELEV_RAW <= RC_PWM_MIN || val_ELEV_RAW >= RC_PWM_MAX) {
		if (val_ELEV_RAW <= RC_PWM_MIN)
			val_ELEV_RAW = RC_PWM_MIN;
		else if (val_ELEV_RAW >= RC_PWM_MAX)
			val_ELEV_RAW = RC_PWM_MAX;
	}
	rc->val_ELEV = map(val_ELEV_RAW, RC_PWM_MIN, RC_PWM_MAX, 100, -100);
}

void rc_get_THRO(Rc *rc) {
	int val_THRO_RAW = pulseIn(rc->pinTHRO, HIGH, PERIOD);
	if (val_THRO_RAW <= RC_PWM_MIN || val_THRO_RAW >= RC_PWM_MAX) {
		if (val_THRO_RAW <= RC_PWM_MIN)
			val_THRO_RAW = RC_PWM_MIN;
		else if (val_THRO_RAW >= RC_PWM_MAX)
			val_THRO_RAW = RC_PWM_MAX;
	}
	rc->val_THRO = map(val_THRO_RAW, RC_PWM_MIN, RC_PWM_MAX, 0, 100);
}

void rc_print(Rc *rc) {
	Serial.print(rc->val_AILE);
	Serial.print(";");
	Serial.print(rc->val_ELEV);
	Serial.print(";");
	Serial.println(rc->val_THRO);
}
