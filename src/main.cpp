#include <Arduino.h>
#include "checkpoint.h"
#include "base.h"

enum Mode{
    checkpoint,
    baseMode,
} mode;
void setup() {
    Serial.begin(9600);
    while (!Serial);

    if(digitalRead(settingButton2))
        mode = baseMode;
    else
        mode = checkpoint;

    if (mode == checkpoint)
        checkpointSetup();
    else
        base::setup();
}

void loop() {
    if (mode == checkpoint)
        checkpointUpdate();
    else
        base::update();
}