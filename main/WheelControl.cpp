#include "WheelControl.h"

WheelControl::WheelControl(const int _Motor_PWM) {
    this->Motor_PWM = _Motor_PWM;
}

void WheelControl::set_Motor_PWM(const int _Motor_PWM) {
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
    MOTORA_FORWARD(this->Motor_PWM);
    MOTORB_FORWARD(this->Motor_PWM);
    MOTORC_FORWARD(this->Motor_PWM);
    MOTORD_FORWARD(this->Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↓A-----B↓
//     |  |  |
//     |  ↓  |
//    ↓C-----D↓
void WheelControl::reverse(void) {
    MOTORA_BACKOFF(this->Motor_PWM);
    MOTORB_BACKOFF(this->Motor_PWM);
    MOTORC_BACKOFF(this->Motor_PWM);
    MOTORD_BACKOFF(this->Motor_PWM);
}

//------------------------------------------------------------------------------
//    =A-----B↑
//     |   ↖ |
//     | ↖   |
//    ↑C-----D=
void WheelControl::left1(void) {
    MOTORA_STOP(this->Motor_PWM);
    MOTORB_FORWARD(this->Motor_PWM);
    MOTORC_FORWARD(this->Motor_PWM);
    MOTORD_STOP(this->Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↓A-----B↑
//     |  ←  |
//     |  ←  |
//    ↑C-----D↓
void WheelControl::left2(void) {
    MOTORA_BACKOFF(this->Motor_PWM);
    MOTORB_FORWARD(this->Motor_PWM);
    MOTORC_FORWARD(this->Motor_PWM);
    MOTORD_BACKOFF(this->Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↓A-----B=
//     | ↙   |
//     |   ↙ |
//    =C-----D↓
void WheelControl::left3(void) {
    MOTORA_BACKOFF(this->Motor_PWM);
    MOTORB_STOP(this->Motor_PWM);
    MOTORC_STOP(this->Motor_PWM);
    MOTORD_BACKOFF(this->Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↑A-----B=
//     | ↗   |
//     |   ↗ |
//    =C-----D↑
void WheelControl::right1(void) {
    MOTORA_FORWARD(this->Motor_PWM);
    MOTORB_STOP(this->Motor_PWM);
    MOTORC_STOP(this->Motor_PWM);
    MOTORD_FORWARD(this->Motor_PWM);
}

//------------------------------------------------------------------------------
//    ↑A-----B↓
//     |  →  |
//     |  →  |
//    ↓C-----D↑
void WheelControl::right2(void) {
    MOTORA_FORWARD(this->Motor_PWM);
    MOTORB_BACKOFF(this->Motor_PWM);
    MOTORC_BACKOFF(this->Motor_PWM);
    MOTORD_FORWARD(this->Motor_PWM);
}

//------------------------------------------------------------------------------
//    =A-----B↓
//     |   ↘ |
//     | ↘   |
//    ↓C-----D=
void WheelControl::right3(void) {
    MOTORA_STOP(this->Motor_PWM);
    MOTORB_BACKOFF(this->Motor_PWM);
    MOTORC_BACKOFF(this->Motor_PWM);
    MOTORD_STOP(this->Motor_PWM);
}

//------------------------------------------------------------------------------
// ↓A-----B↑
//  |     |
//  |     |
// ↓C-----D↑
void WheelControl::turn_left(void) {
    MOTORA_BACKOFF(this->Motor_PWM);
    MOTORB_FORWARD(this->Motor_PWM);
    MOTORC_BACKOFF(this->Motor_PWM);
    MOTORD_FORWARD(this->Motor_PWM);
}

//------------------------------------------------------------------------------
// ↑A-----B↓
//  |     |
//  |     |
// ↑C-----D↓
void WheelControl::turn_right(void) {
    MOTORA_FORWARD(this->Motor_PWM);
    MOTORB_BACKOFF(this->Motor_PWM);
    MOTORC_FORWARD(this->Motor_PWM);
    MOTORD_BACKOFF(this->Motor_PWM);
}

//------------------------------------------------------------------------------
//    =A-----B=
//     |  =  |
//     |  =  |
//    =C-----D=
void WheelControl::stop(void) {
    MOTORA_STOP(this->Motor_PWM);
    MOTORB_STOP(this->Motor_PWM);
    MOTORC_STOP(this->Motor_PWM);
    MOTORD_STOP(this->Motor_PWM);
}
