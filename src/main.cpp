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