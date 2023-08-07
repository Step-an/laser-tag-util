#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include "base.h"
#include "pin-defenition.h"
#include "button-process.h"
#include "settings.h"

namespace base {


    Settings settings;
    bool isReady = true;

    uint32_t currentTime = 0;
    uint32_t lastUpdateTime = 0;

    void setup() {
        Serial.println("Started in base mode");
        if (digitalRead(settingButton1)) {
            waitToUnclicking(settingButton1);
            Serial.println("Settings mode entered");

            auto param0 = processSettingParameter(2);
            if (param0 == 0) {
                settings.mode = life;
            } else if (param0 == 1) {
                settings.mode = ammo;
            }
            logParameter(0, param0);

            auto param1 = processSettingParameter(10);
            logParameter(1, param1);

            auto param2 = processSettingParameter(10);
            logParameter(2, param2);

            settings.triggerTimeMs = param1 * 1000 + param2 * 10000;


            EEPROM.put(baseSettingsAddress, settings);

            Serial.println("Settings accepted");
        }

        EEPROM.get(baseSettingsAddress, settings);

        Serial.print("Mode: ");
        if (settings.mode == ammo){
            Serial.println("ammo recovery");
        } else if (settings.mode == life){
            Serial.println("life recovery");
        }

        Serial.print("Trigger time(ms): ");
        Serial.println(settings.triggerTimeMs);
    }

    void update() {
        if (!isReady)
            syncTime();

        if (isClicking(baseTriggerButton)){
            if (!isReady)
                return;

            createImpulse();
            setReadyState(false);

            currentTime = 0;
            lastUpdateTime = millis();
        }
    }

    void syncTime() {
        uint32_t timeOfChanging = millis();
        currentTime += timeOfChanging - lastUpdateTime;
        lastUpdateTime = timeOfChanging;

        if (currentTime >= settings.triggerTimeMs){
            setReadyState(true);
        }
    }

    void setReadyState(bool state) {
        if (state){
            digitalWrite(notReadyLight, 0);
            digitalWrite(readyLight, 1);
        } else{
            digitalWrite(notReadyLight, 1);
            digitalWrite(readyLight, 0);
        }

        isReady = state;
    }

    void createImpulse() {
        Serial.println("Impulse has been created");
    }
}
