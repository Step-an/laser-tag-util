#include <EEPROM.h>
#include "destroyable-target.h"
#include "pin-defenition.h"
#include "button-process.h"
#include "settings-indication.h"
#include "settings.h"
#include "laser-packet-process.h"

namespace DestroyableTarget {
    Settings settings;

    constexpr uint16_t impulsesInUsLength = 100;
    uint16_t impulsesInUs[impulsesInUsLength];
    int16_t currentHealth;

    bool iSDestroyed = false;

    void setup() {
        if (isClicking(settingButton1)) {
            waitToUnclicking(settingButton1);
            processSettings();
        }

        EEPROM.get(destroyableTargetSettingsAddress, settings);
        currentHealth = settings.hitPoints;
    }

    void update() {
        if (digitalRead(IRReciever) == LOW){
            handleIRSignal();
        }
    }

    void processSettings() {
        enteringLoop(0);
        int param0 = processSettingParameter(10, 0);
        submittingLoop(param0, 0);

        enteringLoop(1);
        int param1 = processSettingParameter(10, 1);
        submittingLoop(param1, 1);

        enteringLoop(2);
        int param2 = processSettingParameter(10, 2);
        submittingLoop(param2, 2);

        settings.hitPoints = param0 + param1 * 10 + param2 * 100;
        EEPROM.put(destroyableTargetSettingsAddress, settings);
    }

    void handleIRSignal() {
        constexpr uint8_t maxAmountParsedImpulses = 100;
        auto irImpulsesLength = getImpulsesInuS(impulsesInUs, impulsesInUsLength, IRReciever);
        uint8_t parsedImpulses[maxAmountParsedImpulses];
        if (!parseImpulses(impulsesInUs, irImpulsesLength, parsedImpulses))
            return;

        uint8_t parsedImpulsesLength = irImpulsesLength - 1;

        auto packetType = parsePacket(parsedImpulses, parsedImpulsesLength);
        if (packetType == command && commandPacket.messageID == 0x83 && commandPacket.messageData == 0x02){
            iSDestroyed = false;
            currentHealth = settings.hitPoints;
            return;
        }

        if (iSDestroyed)
            return;
        if (packetType != shot)
            return;

        currentHealth -= shotPacket.damage;
        if (currentHealth <= 0){
            iSDestroyed = true;
            executeDeadActions();
        }
    }

    void executeDeadActions() {
        while (true){
            if (digitalRead(IRReciever) == LOW){
                handleIRSignal();
                if (!iSDestroyed)
                    return;
            }
            Serial.println("Destroyed");
        }
    }
}