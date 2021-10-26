void rc_init(
	Rc *rc,
	const int pin_AILE,
	const int pin_ELEV,
	const int pin_THRO,
	const int pin_AUX5,
	const int pin_AUX6,
	const int pin_AUX7
) {
	rc->pin_AILE = pin_AILE;
	rc->pin_ELEV = pin_ELEV;
	rc->pin_THRO = pin_THRO;
	rc->pin_AUX5 = pin_AUX5;
	rc->pin_AUX6 = pin_AUX6;
	rc->pin_AUX7 = pin_AUX7;

	rc->val_AILE = 0;
	rc->val_ELEV = 0;
	rc->val_THRO = 0;
	rc->val_AUX5 = 0;
	rc->val_AUX6 = 0;
	rc->val_AUX7 = 0;
}

void rc_io_init(Rc *rc) {
	pinMode(rc->pin_AILE, INPUT);
	pinMode(rc->pin_ELEV, INPUT);
	pinMode(rc->pin_THRO, INPUT);
	pinMode(rc->pin_AUX5, INPUT);
	pinMode(rc->pin_AUX6, INPUT);
	pinMode(rc->pin_AUX7, INPUT);
}

void rc_get_AILE(Rc *rc) {
	int val_AILE_RAW = pulseIn(rc->pin_AILE, HIGH, PERIOD);
	if (val_AILE_RAW <= RC_PWM_MIN || val_AILE_RAW >= RC_PWM_MAX) {
		if (val_AILE_RAW <= RC_PWM_MIN)
			val_AILE_RAW = RC_PWM_MIN;
		else if (val_AILE_RAW >= RC_PWM_MAX)
			val_AILE_RAW = RC_PWM_MAX;
	}
	rc->val_AILE = map(val_AILE_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
}

void rc_get_ELEV(Rc *rc) {
	int val_ELEV_RAW = pulseIn(rc->pin_ELEV, HIGH, PERIOD);
	if (val_ELEV_RAW <= RC_PWM_MIN || val_ELEV_RAW >= RC_PWM_MAX) {
		if (val_ELEV_RAW <= RC_PWM_MIN) {
			val_ELEV_RAW = RC_PWM_MIN;
		} else if (val_ELEV_RAW >= RC_PWM_MAX) {
			val_ELEV_RAW = RC_PWM_MAX;
		}
	}
	rc->val_ELEV = map(val_ELEV_RAW, RC_PWM_MIN, RC_PWM_MAX, 100, -100);
}

void rc_get_THRO(Rc *rc) {
	int val_THRO_RAW = pulseIn(rc->pin_THRO, HIGH, PERIOD);
	if (val_THRO_RAW <= RC_PWM_MIN || val_THRO_RAW >= RC_PWM_MAX) {
		if (val_THRO_RAW <= RC_PWM_MIN) {
			val_THRO_RAW = RC_PWM_MIN;
		} else if (val_THRO_RAW >= RC_PWM_MAX) {
			val_THRO_RAW = RC_PWM_MAX;
		}
	}
	rc->val_THRO = map(val_THRO_RAW, RC_PWM_MIN, RC_PWM_MAX, 0, 100);
}

void rc_get_AUX5(Rc *rc) {
	int val_AUX5_RAW = pulseIn(rc->pin_AUX5, HIGH);
	if (val_AUX5_RAW < 1100) {
		rc->val_AUX5 = -100;
	} else if (val_AUX5_RAW > 1100 && val_AUX5_RAW < 1800) {
		rc->val_AUX5 = 0;
	} else if (val_AUX5_RAW > 1800) {
		rc->val_AUX5 = 100;
	}
}

void rc_get_AUX6(Rc *rc) {
	// I am not quite sure what the behavior of a button press is
}

void rc_get_AUX7(Rc *rc) {
	int val_AUX7_RAW = pulseIn(rc->pin_AUX7, HIGH);
	if (val_AUX7_RAW < 1100) {
		rc->val_AUX7 = -100;
	} else if (val_AUX7_RAW > 1100 && val_AUX7_RAW < 1800) {
		rc->val_AUX7 = 0;
	} else if (val_AUX7_RAW > 1800) {
		rc->val_AUX7 = 100;
	}
}

void rc_print(Rc *rc) {
	Serial.print(rc->val_AILE);
	Serial.print(";");
	Serial.print(rc->val_ELEV);
	Serial.print(";");
	Serial.print(rc->val_THRO);
	Serial.print(";");
	Serial.print(rc->val_AUX5);
	Serial.print(";");
	Serial.print(rc->val_AUX6);
	Serial.print(";");
	Serial.println(rc->val_AUX7);
}
