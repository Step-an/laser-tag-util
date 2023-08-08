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
constexpr uint8_t settingButton3 = 42;
constexpr uint8_t settingButton4 = 47;
constexpr uint8_t settingButton5 = 48;

constexpr uint8_t indicatorLight1 = 49;
constexpr uint8_t indicatorLight2 = 41;

constexpr uint8_t baseTriggerButton = 18;

constexpr uint8_t readyLight = 43;
constexpr uint8_t notReadyLight = 44;

#endif //CHECKPOINT_PIN_DEFENITION_H
