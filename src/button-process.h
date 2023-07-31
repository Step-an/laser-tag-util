#ifndef CHECKPOINT_BUTTON_PROCESS_H
#define CHECKPOINT_BUTTON_PROCESS_H

#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>

constexpr uint8_t buttonProtectionMs = 50;

bool isClicking(uint8_t button);
void waitToUnclicking(uint8_t button);

#endif //CHECKPOINT_BUTTON_PROCESS_H
