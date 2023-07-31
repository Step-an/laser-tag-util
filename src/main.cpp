#include <Arduino.h>
#include "checkpoint.h"
#include "base.h"

enum Mode{
    checkpoint,
    base,
} mode;
void setup() {
    Serial.begin(9600);
    while (!Serial);

    if(digitalRead(settingButton2))
        mode = base;
    else
        mode = checkpoint;

    if (mode == checkpoint)
        checkpointSetup();
    else
        baseSetup();
}

void loop() {
    if (mode == checkpoint)
        checkpointUpdate();
    else
        baseUpdate();
}