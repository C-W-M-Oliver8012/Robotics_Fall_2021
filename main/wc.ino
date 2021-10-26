void wc_init(Wc *wc, const int motor_pwd) {
	wc->is_automatic = false;
	wc->motor_pwd = motor_pwd;
}

void wc_io_init(Wc *wc) {
	pinMode(PWMA, OUTPUT);
	pinMode(DIRA, OUTPUT);
	pinMode(PWMB, OUTPUT);
	pinMode(DIRB, OUTPUT);
	pinMode(PWMC, OUTPUT);
	pinMode(DIRC, OUTPUT);
	pinMode(PWMD, OUTPUT);
	pinMode(DIRD, OUTPUT);
	wc_stop(wc);

	// for automatic
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	digitalWrite(TRIG_PIN, LOW);

	wc->head.attach(SERVO_PIN);
	wc->head.write(90);
	delay(2000);
}

//    ↑A-----B↑
//     |  ↑  |
//     |  |  |
//    ↑C-----D↑
void wc_forward(Wc *wc) {
	MOTORA_FORWARD(wc->motor_pwd);
	MOTORB_FORWARD(wc->motor_pwd);
	MOTORC_FORWARD(wc->motor_pwd);
	MOTORD_FORWARD(wc->motor_pwd);
}

//    ↓A-----B↓
//     |  |  |
//     |  ↓  |
//    ↓C-----D↓
void wc_reverse(Wc *wc) {
	MOTORA_BACKOFF(wc->motor_pwd);
	MOTORB_BACKOFF(wc->motor_pwd);
	MOTORC_BACKOFF(wc->motor_pwd);
	MOTORD_BACKOFF(wc->motor_pwd);
}

// ↓A-----B↑
//  |     |
//  |     |
// ↓C-----D↑
void wc_turn_left(Wc *wc) {
	MOTORA_BACKOFF(wc->motor_pwd);
	MOTORB_FORWARD(wc->motor_pwd);
	MOTORC_BACKOFF(wc->motor_pwd);
	MOTORD_FORWARD(wc->motor_pwd);
}

// ↑A-----B↓
//  |     |
//  |     |
// ↑C-----D↓
void wc_turn_right(Wc *wc) {
	MOTORA_FORWARD(wc->motor_pwd);
	MOTORB_BACKOFF(wc->motor_pwd);
	MOTORC_FORWARD(wc->motor_pwd);
	MOTORD_BACKOFF(wc->motor_pwd);
}

//    =A-----B=
//     |  =  |
//     |  =  |
//    =C-----D=
void wc_stop(Wc *wc) {
	MOTORA_STOP(wc->motor_pwd);
	MOTORB_STOP(wc->motor_pwd);
	MOTORC_STOP(wc->motor_pwd);
	MOTORD_STOP(wc->motor_pwd);
}

// echo_distance probably should be a double
// the conversion does not make sense if echo_distance is a long
int wc_watch(void) {
	long echo_distance;
	digitalWrite(TRIG_PIN, LOW);
	delayMicroseconds(5);
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(15);
	digitalWrite(TRIG_PIN, LOW);
	echo_distance = pulseIn(ECHO_PIN, HIGH);
	echo_distance *= 0.01657; // convert to cm
	return round(echo_distance);
}

//Meassures distances to the left,center,right return a
String wc_watch_surrounding(Wc *wc) {
	/* obstacle_status is a binary integer, its last 3 digits stands for if
	 * there is any obstacles in left front,direct front and right front
	 * directions, 3 digit string, for example 100 means front left front has
	 * obstacle, 011 means direct front and right front have obstacles
	 */
	int obstacle_status = B1000;

	//senfor facing left front direction
	wc->head.write(160);
	delay(400);
	int distance = wc_watch();
	if (distance < OBSTACLE_LIMIT) {
		wc_stop(wc);
		obstacle_status = obstacle_status | B100;
	}

	//sensor facing direct front
	wc->head.write(90);
	delay(400);
	distance = wc_watch();
	if (distance < OBSTACLE_LIMIT) {
		wc_stop(wc);
		obstacle_status = obstacle_status | B10;
	}

	//sensor faces to right front 20 degree direction
	wc->head.write(20);
	delay(400);
	distance = wc_watch();
	if (distance < OBSTACLE_LIMIT) {
		wc_stop(wc);
		obstacle_status = obstacle_status | 1;
	}

	String obstacle_str = String(obstacle_status, BIN);
	obstacle_str = obstacle_str.substring(1, 4);

	//return 5-character string standing for 5 direction obstacle status
	return obstacle_str;
}

void wc_auto_avoidance(Wc *wc) {
	// 5 digits of obstacle_sign binary value means the 5 direction obstacle status
	String obstacle_sign = wc_watch_surrounding(wc);
	Serial.print("begin str=");
	Serial.println(obstacle_sign);
	if (obstacle_sign == "100") {
		Serial.println("SLIT right");
		wc_turn_right(wc);
		delay(TURN_TIME);
		wc_stop(wc);
	} else if (obstacle_sign == "001") {
		Serial.println("SLIT LEFT");
		wc_turn_left(wc);
		delay(TURN_TIME);
		wc_stop(wc);
	} else if (obstacle_sign == "110") {
		Serial.println("hand right");
		wc_turn_right(wc);
		delay(TURN_TIME);
		wc_stop(wc);
	} else if (obstacle_sign == "011" || obstacle_sign == "010") {
		Serial.println("hand left");
		wc_turn_left(wc);
		delay(TURN_TIME);
		wc_stop(wc);
	} else if (obstacle_sign == "111" || obstacle_sign == "101") {
		Serial.println("hand back left");
		wc_turn_right(wc);
		delay(BACK_TIME);
		wc_stop(wc);
	} else if (obstacle_sign == "000") {
		Serial.println("go ahead");
		wc_forward(wc);
		delay(FORWARD_TIME);
		wc_stop(wc);
	}
}
