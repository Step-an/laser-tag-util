#ifndef CHECKPOINT_PIN_DEFENITION_H
#define CHECKPOINT_PIN_DEFENITION_H

#include <stdint.h>

constexpr struct LoRaPins{
    uint8_t ss = 53;
    uint8_t mosi = 51;
    uint8_t miso = 50;
    uint8_t sck = 52;
    uint8_t rst = 8;
    uint8_t dio0 = 2;
} lorapins;

// IR
constexpr uint8_t IRReciever = 3;


// Settings buttons
constexpr uint8_t settingButton1 = 14;
constexpr uint8_t settingButton2 = 15;

#endif //CHECKPOINT_PIN_DEFENITION_H
