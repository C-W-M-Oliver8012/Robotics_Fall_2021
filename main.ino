#include "RCControl.h"
#include "WheelControl.h"

// These numbers will likely need to be changed
RCControl RCControl(39, 40, 41, 42, 43, 44, 45);

// does setting WheelControl.pwm to WHEEL_MIN_PWM stop the motor or should
// it be set to zero
WheelControl WheelControl(WHEEL_MIN_PWM);

void setup() {
    // 9600 probably needs changed. This should be defined somewhere
    Serial.begin(9600);
    WheelControl.io_init();
}

void loop() {
    // These names do not 100% map to the new controller
    // but everything should still work I think
    // See "https://www.radiolink.com/t8s_manual" for more info
    int val_THRO = RCControl.get_THRO();
    int val_AILE = RCControl.get_AILE();
    int val_ELEV = RCControl.get_ELEV();
    int val_RUDD = RCControl.get_RUDD();
    int val_GEAR = RCControl.get_GEAR();
    int val_AUX1 = RCControl.get_AUX1();
    int val_AUX2 = RCControl.get_AUX2();

    // prints values
    RCControl.print_manual();

    if (val_THRO >= POS_THRES) {
        WheelControl.set_Motor_PWM(
           map(val_THRO, POS_THRES, 100, WHEEL_MIN_PWM, WHEEL_MAX_PWM)
        );
    } else {
        WheelControl.stop();
    }

    // POS_THRES and NEG_THRES are defined in RCControl.h
    // I believe that this is how the controller maps but I could be wrong

    // up and left
    if (val_ELEV >= POS_THRES && val_AILE >= POS_THRES) {
        WheelControl.left1();
    // down and left
    } else if (val_ELEV <= NEG_THRES && val_AILE >= POS_THRES) {
        WheelControl.left3();
    // up and right
    } else if (val_ELEV >= POS_THRES && val_AILE <= NEG_THRES) {
        WheelControl.right1();
    // down and right
    } else if (val_ELEV <= NEG_THRES && val_AILE <= NEG_THRES) {
        WheelControl.right3();
    // up
    } else if (val_ELEV >= POS_THRES) {
        WheelControl.forward();
    // down
    } else if (val_ELEV <= NEG_THRES) {
        WheelControl.reverse();
    // left
    } else if (val_AILE >= POS_THRES) {
        // Not sure which we want
        //WheelControl.left2();
        WheelControl.turn_left();
    // right
    } else if (val_AILE <= NEG_THRES) {
        // Not sure which we want
        //WheelControl.right2();
        WheelControl.turn_right();
    // stop
    } else {
        WheelControl.stop();
    }
}
