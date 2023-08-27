#include "button-process.h"
#include "settings-indication.h"

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

int processSettingParameter(uint8_t parametersAmount, int loopNumber) {
    int parameter = 0;
    iterationInLoop(parameter, loopNumber);
    while (true){
        if (isClicking(settingButton1)){
            if (parameter < parametersAmount - 1){
                ++parameter;
            } else if (parameter == parametersAmount - 1){
                parameter = 0;
            }

            waitToUnclicking(settingButton1);
            iterationInLoop(parameter, loopNumber);
        }

        if (isClicking(settingButton2)){
            waitToUnclicking(settingButton2);
            return parameter;
        }
    }
}