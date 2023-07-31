#include "button-process.h"

bool isClicking(uint8_t button) {
    if(digitalRead(button) == true){
        delay(buttonProtectionMs);
        if (digitalRead(button) == true)
            return true;
    }
    return false;
}

void waitToUnclicking(uint8_t button) {
    while(1){
        if(digitalRead(button) == 0){
            delay(buttonProtectionMs);
            if(digitalRead(button) == 0)
                break;
        }
    }
}