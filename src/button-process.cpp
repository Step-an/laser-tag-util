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

int processSettingParameter(uint8_t parametersAmount) {
    int parameter = 0;
    while (true){
        if (isClicking(settingButton1)){
            if (parameter < parametersAmount - 1){
                ++parameter;
            } else if (parameter == parametersAmount - 1){
                parameter = 0;
            }

            waitToUnclicking(settingButton1);
            Serial.print("Current parameter has been set to ");
            Serial.print(parameter);
            Serial.println(".");
        }

        if (isClicking(settingButton2)){
            waitToUnclicking(settingButton2);
            return parameter;
        }
    }
}

void logParameter(int parameterNumber, int parameterValue) {
    Serial.print("Parameter ");
    char parameterNumberInString[4];
    itoa(parameterNumber, parameterNumberInString, 4);
    Serial.print(parameterNumberInString);

    Serial.print(" has been set to ");

    char parameterValueInString[4];
    itoa(parameterValue, parameterValueInString, 4);
    Serial.print(parameterValueInString);
    Serial.println(".");
}
