#include <Arduino.h>
#include "checkpoint.h"
#include "base.h"

enum Mode{
    checkpointMode,
    baseMode,
} mode;
void setup() {
    Serial.begin(9600);
    while (!Serial);

    pinMode(settingButton1, INPUT);
    pinMode(settingButton2, INPUT);
    pinMode(settingButton3, INPUT);
    pinMode(settingButton4, INPUT);
    pinMode(settingButton5, INPUT);

    pinMode(IRReciever, INPUT);

    pinMode(baseTriggerButton, INPUT);

    pinMode(readyLight, OUTPUT);
    pinMode(notReadyLight, OUTPUT);
    if(digitalRead(settingButton2))
        mode = baseMode;
    else
        mode = checkpointMode;

    if (mode == checkpointMode)
        checkpoint::setup();
    else
        base::setup();
}

void loop() {
    if (mode == checkpointMode)
        checkpoint::update();
    else
        base::update();
}