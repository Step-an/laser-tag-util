#include "checkpoint.h"
#include "settings.h"
#include "settings-indication.h"
#include "laser-packet-process.h"

namespace checkpoint {
    uint32_t teamsTime[4]{0, 0, 0, 0};
    uint32_t lastChangingTime = 0;
    Team currentTeam = None;
    constexpr uint16_t impulsesInUsLength = 100;

    uint16_t impulsesInUs[impulsesInUsLength];
    Settings settings;

    void setup() {
        Serial.println("Started in checkpoint mode");
        pinMode(IRReciever, INPUT);
        EEPROM.get(checkpointSettingsAddress, settings);
        Serial.print("Current trigger time(ms): ");
        Serial.print(settings.triggermS);
        Serial.println(".");
        if (digitalRead(settingButton1)) {
            waitToUnclicking(settingButton1);
            Serial.println("Settings mode entered");
            settings.triggermS = processSettingsMode();
            EEPROM.put(checkpointSettingsAddress, settings);
            Serial.println("Settings accepted");
            Serial.print("Trigger time(ms): ");
            Serial.println(settings.triggermS);
        }
    }

    void syncTeamsTime() {
        if (currentTeam == None) {
            lastChangingTime = millis();
            return;
        }
        uint32_t timeOfChanging = millis();
        teamsTime[currentTeam] += timeOfChanging - lastChangingTime;
        lastChangingTime = timeOfChanging;
        if (teamsTime[currentTeam] >= settings.triggermS) {
            Serial.print("The end. Winner: ");
            Serial.print(teamToTeamName(currentTeam));
            Serial.println(" team.");
            while (true);
        }
    }

    char const *teamToTeamName(Team team) {
        switch (team) {
            case Red:
                return "red";
            case Blue:
                return "blue";
            case Yellow:
                return "yellow";
            case Green:
                return "green";
            case None:
                return "none";
        }
    }

    void processIRSignal(uint8_t IRPin) {
        constexpr uint16_t impulsesMax = 100;
        uint16_t impulsesuS[impulsesMax];

        uint16_t rawImpulsesLength = getImpulsesInuS(impulsesuS, impulsesMax, IRReciever);

        uint8_t packet[impulsesMax];
        if (!parseImpulses(impulsesuS, rawImpulsesLength, packet))
            return;

        uint16_t packetSize = rawImpulsesLength - 1;
        auto pType = parsePacket(packet, packetSize);

        if(pType == command && commandPacket.messageID == 0x83 && commandPacket.messageData == 0x02){
            currentTeam = None;
            for (int i = 0; i < 4; ++i) {
                teamsTime[i] = 0;
            }
            lastChangingTime = millis();
            Serial.println("Current team has been reset");
            return;
        }

        if (pType != shot)
            return;

        currentTeam = static_cast<Team>(shotPacket.shooterTeam);
        Serial.print("Recapturing. New team: ");
        Serial.println(teamToTeamName(currentTeam));
    }

    uint32_t processSettingsMode() {
        static constexpr int parametersAmount = 4;
        uint32_t parameters[parametersAmount];
        for (int i = 0; i < parametersAmount; ++i) {
            enteringLoop(i);
            parameters[i] = processSettingParameter(10, i);
            submittingLoop(parameters[i], i);
        }

        return (parameters[0] + parameters[1] * 10 + parameters[2] * 60 + parameters[3] * 10 * 60) * 1000;
    }

    void update() {
        syncTeamsTime();
        if (digitalRead(IRReciever) == 0)
            processIRSignal(IRReciever);
    }
}