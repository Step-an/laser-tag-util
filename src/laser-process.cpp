#include "laser-process.h"

uint16_t getImpulsesInuS(uint16_t *result, uint16_t max, uint8_t IRPin) {
    uint16_t i = 0;
    while(true){
        if(i == max){
            return 0;
        }

        uint16_t impulseWidthUs = 0;
        while(digitalRead(IRPin) == 0){
            _delay_us(100);
            impulseWidthUs += 100;
        }
        result[i] = impulseWidthUs;
        ++i;

        uint16_t delayUs = 0;
        while(digitalRead(IRPin) == 1){
            _delay_us(100);
            delayUs += 100;
            if(delayUs > 800){
                return i;
            }
        }
    }

    return 0;
}

bool parseImpulses(const uint16_t *impulses, uint16_t length, uint8_t *result) {
    if(!(impulses[0] <= 3000 && impulses[0] >= 1800)){
//        Serial.println("la");
        return false;
    }

    for(uint16_t i = 1; i < length; ++i){
        if(impulses[i] <= 800 && impulses[i] >= 350){
            result[i - 1] = 0;
        } else if(impulses[i] >= 900 && impulses[i] <= 1500){
            result[i - 1] = 1;
        } else{
//            Serial.println("la2");
            return false;
        }
    }
    return true;
}
