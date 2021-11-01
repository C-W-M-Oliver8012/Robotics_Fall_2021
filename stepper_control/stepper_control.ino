//Control Pins for moving the frame up or down
#define frame_stepPin 2
#define frame_dirPin 3
//#define frame_enablePin 4

//Control Pins for open and close the gripper
#define grip_stepPin 5
#define grip_dirPin 6
//#define grip_enablePin 7

//#define stepsPerRevolution 1600

//Control boolean
boolean frameup = false;
boolean framedown = false;
boolean gripclose = false;
boolean gripopen = false;

//Time for controlling the steppers
unsigned long curMillis;
unsigned long prevStepMillis = 0;
unsigned long millisBetweenSteps = 1; // milliseconds - the lower the faster

int inputByte = 0; //the data input from serial communication of the Arduino Mega

void setup(void) {
    Serial.begin(115200);
    pinMode(frame_stepPin,OUTPUT);
    pinMode(frame_dirPin,OUTPUT);
    //pinMode(frame_enablePin,OUTPUT);
    pinMode(grip_stepPin,OUTPUT);
    pinMode(grip_dirPin,OUTPUT);
    //pinMode(grip_enablePin,OUTPUT);
}

void loop(void) {
    curMillis = millis();
    readSerial();
    runCommand();
}

void readSerial(void) {
    frameup = false;
    framedown = false;
    gripclose = false;
    gripopen = false;

    if (Serial.available() > 0) {
        inputByte = Serial.read();
    }
    //Control based on input from Arudino Mega
    if (inputByte == 1) {
        frameup = true;
        framedown = false;
        gripclose = true;
        gripopen = false;
    } else if (inputByte == 2) {
        frameup = true;
        framedown = false;
        gripclose = false;
        gripopen = false;
    } else if (inputByte == 3) {
        frameup = true;
        framedown = false;
        gripclose = false;
        gripopen = true;
    } else if (inputByte == 4) {
        frameup = false;
        framedown = false;
        gripclose = true;
        gripopen = false;
    } else if (inputByte == 5) {
        frameup = false;
        framedown = false;
        gripclose = false;
        gripopen = false;
    } else if (inputByte == 6) {
        frameup = false;
        framedown = false;
        gripclose = false;
        gripopen = true;
    } else if (inputByte == 7) {
        frameup = false;
        framedown = true;
        gripclose = true;
        gripopen = false;
    } else if (inputByte == 8) {
        frameup = false;
        framedown = true;
        gripclose = false;
        gripopen = false;
    } else if (inputByte == 9) {
        frameup = false;
        framedown = true;
        gripclose = false;
        gripopen = true;
    }
}

void runCommand(void) {
    //chose to move either the frame or grip. It seems if the frame is moving the grip will be disable
    if (frameup == true) {
        digitalWrite(frame_dirPin,HIGH);
        frame_singleStep();
    } else if (framedown == true) {
        digitalWrite(frame_dirPin,LOW);
        frame_singleStep();
    }

    if (gripclose == true) {
        digitalWrite(grip_dirPin,HIGH);
        grip_singleStep();
    } else if (gripopen == true) {
        digitalWrite(grip_dirPin,LOW);
        grip_singleStep();
    }
}

void frame_singleStep(void) {
    if (curMillis - prevStepMillis >= millisBetweenSteps) {
        prevStepMillis = curMillis;
        digitalWrite(frame_stepPin, HIGH);
        digitalWrite(frame_stepPin, LOW);
    }
}

void grip_singleStep(void) {
    if (curMillis - prevStepMillis >= millisBetweenSteps) {
        prevStepMillis = curMillis;
        digitalWrite(grip_stepPin, HIGH);
        digitalWrite(grip_stepPin, LOW);
    }
}
