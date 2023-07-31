#ifndef CHECKPOINT_CHECKPOINT_H
#define CHECKPOINT_CHECKPOINT_H

#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include "pin-defenition.h"
#include "button-process.h"
#include "laser-process.h"

enum Team : uint8_t {
    Red = 0,
    Blue = 1,
    Yellow = 2,
    Green = 3,
    None = 4,
};

void checkpointSetup();

void checkpointUpdate();
char const *teamToTeamName(Team team);

void syncTeamsTime();


void processIRSignal(uint8_t IRPin);

uint32_t processSettingsMode();
#endif //CHECKPOINT_CHECKPOINT_H
