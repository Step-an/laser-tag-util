#include <Arduino.h>
#include "checkpoint.h"
#include "base.h"
#include "destroyable-target.h"

enum Mode{
    checkpointMode,
    baseMode,
    destroyableTargetMode,
} mode;
void (*startup)() = nullptr;
void (*update)() = nullptr;
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

    if (isClicking(settingButton2) && isClicking(settingButton3)){
        mode = destroyableTargetMode;
        startup = DestroyableTarget::setup;
        update = DestroyableTarget::update;
    } else if (isClicking(settingButton2) && !isClicking(settingButton3)){
        mode = baseMode;
        startup = base::setup;
        update = base::update;
    } else if (!isClicking(settingButton2) && !isClicking(settingButton3)){
        mode = checkpointMode;
        startup = checkpoint::setup;
        update = checkpoint::update;
    }

    startup();
}

void loop() {
    setup();
}