#ifndef CHECKPOINT_LASER_PROCESS_H
#define CHECKPOINT_LASER_PROCESS_H
#include <Arduino.h>
#include <SPI.h>

uint16_t getImpulsesInuS(uint16_t *result, uint16_t max, uint8_t IRPin);

bool parseImpulses(const uint16_t *impulses, uint16_t length, uint8_t *result);
#endif //CHECKPOINT_LASER_PROCESS_H
