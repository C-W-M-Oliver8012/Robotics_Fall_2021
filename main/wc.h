#ifndef WC
#define WC

#define PWMA 3
#define DIRA 2
#define PWMB 5
#define DIRB 4
#define PWMC 6
#define DIRC 7
#define PWMD 9
#define DIRD 8

#define MOTORA_FORWARD(pwm)    do{digitalWrite(DIRA,LOW); analogWrite(PWMA,pwm);}while(0)
#define MOTORA_STOP(x)         do{digitalWrite(DIRA,LOW); analogWrite(PWMA,0);}while(0)
#define MOTORA_BACKOFF(pwm)    do{digitalWrite(DIRA,HIGH); analogWrite(PWMA,pwm);}while(0)

#define MOTORB_FORWARD(pwm)    do{digitalWrite(DIRB,HIGH); analogWrite(PWMB,pwm);}while(0)
#define MOTORB_STOP(x)         do{digitalWrite(DIRB,LOW); analogWrite(PWMB,0);}while(0)
#define MOTORB_BACKOFF(pwm)    do{digitalWrite(DIRB,LOW); analogWrite(PWMB,pwm);}while(0)

#define MOTORC_FORWARD(pwm)    do{digitalWrite(DIRC,LOW); analogWrite(PWMC,pwm);}while(0)
#define MOTORC_STOP(x)         do{digitalWrite(DIRC,LOW); analogWrite(PWMC,0);}while(0)
#define MOTORC_BACKOFF(pwm)    do{digitalWrite(DIRC,HIGH); analogWrite(PWMC,pwm);}while(0)

#define MOTORD_FORWARD(pwm)    do{digitalWrite(DIRD,HIGH); analogWrite(PWMD,pwm);}while(0)
#define MOTORD_STOP(x)         do{digitalWrite(DIRD,LOW); analogWrite(PWMD,0);}while(0)
#define MOTORD_BACKOFF(pwm)    do{digitalWrite(DIRD,LOW); analogWrite(PWMD,pwm);}while(0)

#define WHEEL_MAX_PWM 150
#define WHEEL_MIN_PWM 50

typedef struct Wc {
	int motor_pwd;
} Wc;

void wc_init(Wc *wc, const int motor_pwd);
void wc_io_init(Wc *wc);
void wc_forward(Wc *wc);
void wc_reverse(Wc *wc);
void wc_turn_left(Wc *wc);
void wc_turn_right(Wc *wc);
void wc_stop(Wc *wc);

#endif