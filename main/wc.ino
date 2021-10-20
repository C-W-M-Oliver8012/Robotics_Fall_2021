void wc_init(Wc *wc, const int motor_pwd) {
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
