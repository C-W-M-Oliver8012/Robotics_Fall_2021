#include "WheelControl.h"

WheelControl::WheelControl(int _Motor_PWM) {
    this->Motor_PWM = _Motor_PWM;
}

void WheelControl::set_Motor_PWM(int _Motor_PWM) {
    this->Motor_PWM = _Motor_PWM;
}

void WheelControl::io_init(void) {
    pinMode(PWMA, OUTPUT);
    pinMode(DIRA1, OUTPUT);
    pinMode(DIRA2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(DIRB1, OUTPUT);
    pinMode(DIRB2, OUTPUT);
    pinMode(PWMC, OUTPUT);
    pinMode(DIRC1, OUTPUT);
    pinMode(DIRC2, OUTPUT);
    pinMode(PWMD, OUTPUT);
    pinMode(DIRD1, OUTPUT);
    pinMode(DIRD2, OUTPUT);
    this->stop();
}

//------------------------------------------------------------------------------
//    ↑A-----B↑
//     |  ↑  |
//     |  |  |
//    ↑C-----D↑
void WheelControl::forward(void) {
  MOTORA_FORWARD(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↓A-----B↓
//     |  |  |
//     |  ↓  |
//    ↓C-----D↓
void WheelControl::reverse(void) {
  MOTORA_BACKOFF(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}

//------------------------------------------------------------------------------
//    =A-----B↑
//     |   ↖ |
//     | ↖   |
//    ↑C-----D=
void WheelControl::left1(void) {
  MOTORA_STOP(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_STOP(Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↓A-----B↑
//     |  ←  |
//     |  ←  |
//    ↑C-----D↓
void WheelControl::left2(void) {
  MOTORA_BACKOFF(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↓A-----B=
//     | ↙   |
//     |   ↙ |
//    =C-----D↓
void WheelControl::left3(void) {
  MOTORA_BACKOFF(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↑A-----B=
//     | ↗   |
//     |   ↗ |
//    =C-----D↑
void WheelControl::right1(void) {
  MOTORA_FORWARD(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↑A-----B↓
//     |  →  |
//     |  →  |
//    ↓C-----D↑
void WheelControl::right2(void) {
  MOTORA_FORWARD(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}

//------------------------------------------------------------------------------
//    =A-----B↓
//     |   ↘ |
//     | ↘   |
//    ↓C-----D=
void WheelControl::right3(void) {
  MOTORA_STOP(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_STOP(Motor_PWM);
}

//------------------------------------------------------------------------------
// ↓A-----B↑
//  |     |
//  |     |
// ↓C-----D↑
void WheelControl::turn_left(void) {
  MOTORA_BACKOFF(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}

//------------------------------------------------------------------------------
// ↑A-----B↓
//  |     |
//  |     |
// ↑C-----D↓
void WheelControl::turn_right(void) {
  MOTORA_FORWARD(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}

//------------------------------------------------------------------------------
//    =A-----B=
//     |  =  |
//     |  =  |
//    =C-----D=
void WheelControl::stop(void) {
  MOTORA_STOP(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_STOP(Motor_PWM);
}
