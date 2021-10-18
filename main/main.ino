#include "RCControl.h"
#include "WheelControl.h"

#define SERIAL_NUMBER 115200

// These numbers will likely need to be changed
RCControl RCControl(41, 39, 40, 42, 43, 44, 45);
WheelControl WheelControl(0);

void setup() {
    Serial.begin(SERIAL_NUMBER);
    WheelControl.io_init();
}

void loop() {
    // These names do not 100% map to the new controller
    // but everything should still work I think
    // See "https://www.radiolink.com/t8s_manual" for more info
    const int val_THRO = RCControl.get_THRO();
    const int val_AILE = RCControl.get_AILE();
    const int val_ELEV = RCControl.get_ELEV();
    const int val_RUDD = RCControl.get_RUDD();
    const int val_GEAR = RCControl.get_GEAR();
    const int val_AUX1 = RCControl.get_AUX1();
    const int val_AUX2 = RCControl.get_AUX2();

    // prints values
    RCControl.print_manual();

    // sets speed
    if (val_THRO >= POS_THRES) {
        WheelControl.set_Motor_PWM(
           map(val_THRO, POS_THRES, 100, 1, 255)
        );
    } else {
        WheelControl.set_Motor_PWM(0);
        WheelControl.stop();
    }

    // up
    if (val_ELEV >= POS_THRES) {
        WheelControl.forward();
    // down
    } else if (val_ELEV <= NEG_THRES) {
        WheelControl.reverse();
    // left
    } else if (val_AILE >= POS_THRES) {
        // Not sure which we want
        WheelControl.turn_left();
    // right
    } else if (val_AILE <= NEG_THRES) {
        // Not sure which we want
        WheelControl.turn_right();
    // stop
    } else {
        WheelControl.stop();
    }
}
