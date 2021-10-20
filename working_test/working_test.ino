#define PERIOD           30000
#define RC_PWM_MIN       990
#define RC_PWM_MAX       1980
#define POS_THRES        15
#define NEG_THRES        -15

//Define Controller Pins
#define pinAILE 39
#define pinELEV 40
#define pinTHRO 41

//Define Motor Pins
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

#define WHEEL_MAX_PWM   150
#define WHEEL_MIN_PWM   50
int Motor_PWM = 0;

//******************Get Controller Values*******************************
int get_AILE(void) {
  int val_AILE;
  int val_AILE_RAW = pulseIn(pinAILE, HIGH, PERIOD);
  //Serial.println(val_AILE_RAW);
  if (val_AILE_RAW <= RC_PWM_MIN || val_AILE_RAW >= RC_PWM_MAX) {
    if (val_AILE_RAW <= RC_PWM_MIN)
      val_AILE_RAW = RC_PWM_MIN;
    else if (val_AILE_RAW >= RC_PWM_MAX)
      val_AILE_RAW = RC_PWM_MAX;
  }
  val_AILE = map(val_AILE_RAW, RC_PWM_MIN, RC_PWM_MAX, -100, 100);
  return val_AILE;
}

int get_ELEV(void) {
  int val_ELEV;
  int val_ELEV_RAW = pulseIn(pinELEV, HIGH, PERIOD);
  if (val_ELEV_RAW <= RC_PWM_MIN || val_ELEV_RAW >= RC_PWM_MAX) {
    if (val_ELEV_RAW <= RC_PWM_MIN)
      val_ELEV_RAW = RC_PWM_MIN;
    else if (val_ELEV_RAW >= RC_PWM_MAX)
      val_ELEV_RAW = RC_PWM_MAX;
  }
  val_ELEV = map(val_ELEV_RAW, RC_PWM_MIN, RC_PWM_MAX, 100, -100);
  return val_ELEV;
}

int get_THRO(void) {
  int val_THRO;
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

//********************Motor Movements********************************
//    ↑A-----B↑
//     |  ↑  |
//     |  |  |
//    ↑C-----D↑
void ADVANCE()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}

//    ↓A-----B↓
//     |  |  |
//     |  ↓  |
//    ↓C-----D↓
void BACK()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    =A-----B↑
//     |   ↖ |
//     | ↖   |
//    ↑C-----D=
void LEFT_1()
{
  MOTORA_STOP(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_STOP(Motor_PWM);
}

//    ↓A-----B↑
//     |  ←  |
//     |  ←  |
//    ↑C-----D↓
void LEFT_2()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    ↓A-----B=
//     | ↙   |
//     |   ↙ |
//    =C-----D↓
void LEFT_3()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    ↑A-----B=
//     | ↗   |
//     |   ↗ |
//    =C-----D↑
void RIGHT_1()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}
//    ↑A-----B↓
//     |  →  |
//     |  →  |
//    ↓C-----D↑
void RIGHT_2()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}
//    =A-----B↓
//     |   ↘ |
//     | ↘   |
//    ↓C-----D=
void RIGHT_3()
{
  MOTORA_STOP(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_STOP(Motor_PWM);
}
// ↓A-----B↑
//  |     |
//  |     |
// ↓C-----D↑
void TURN_LEFT()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}
// ↑A-----B↓
//  |     |
//  |     |
// ↑C-----D↓
void TURN_RIGHT()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    =A-----B=
//     |  =  |
//     |  =  |
//    =C-----D=
void STOP()
{
  MOTORA_STOP(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_STOP(Motor_PWM);
}

void setup() {
  Serial.begin(115200);
  //Initial Controller Pins
  pinMode(pinAILE, INPUT);
  pinMode(pinELEV, INPUT);
  pinMode(pinTHRO, INPUT);
  //Initial Motor Pins
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMC, OUTPUT);
  pinMode(DIRC, OUTPUT);
  pinMode(PWMD, OUTPUT);
  pinMode(DIRD, OUTPUT);
  STOP();
}

void loop() {
  Serial.print(get_AILE());
  Serial.print(";");
  Serial.print(get_ELEV());
  Serial.print(";");
  Serial.println(get_THRO());

  int val_AILE = get_AILE();
  int val_ELEV = get_ELEV();
  int val_THRO = get_THRO();

  //Set Motor PWM from Throttle
  if(val_THRO >= POS_THRES) {
    Motor_PWM = map(val_THRO, POS_THRES, 100, 1, 255);
  }
  else {
    Motor_PWM = 0;
    STOP();
  }
  if (val_ELEV >= POS_THRES && val_AILE >= POS_THRES) {
    LEFT_1();
  }
  else if (val_ELEV <= NEG_THRES && val_AILE >= POS_THRES) {
    LEFT_3();
  }
  else if (val_ELEV >= POS_THRES && val_AILE <= NEG_THRES) {
    RIGHT_1();
  }
  else if (val_ELEV <= NEG_THRES && val_AILE <= NEG_THRES) {
    RIGHT_3();
  }
  else if(val_ELEV >= POS_THRES) {
    ADVANCE();
  }
  else if(val_ELEV <= NEG_THRES) {
    BACK();
  }
  else if(val_AILE <= NEG_THRES) {
    TURN_LEFT();
  }
  else if(val_AILE >= POS_THRES) {
    TURN_RIGHT();
  }
  else {
    STOP();
  }
}
