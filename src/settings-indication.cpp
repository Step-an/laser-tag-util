#include "settings-indication.h"
#include "pin-defenition.h"
#include <Arduino.h>
#include <SPI.h>

bool isCurrentLight1 = false;

void enteringLoop(int loopNumber) {

}

void iterationInLoop(int itemNumber, int loopNumber) {
    Serial.print("Current parameter has been set to ");
    Serial.print(itemNumber);
    Serial.println(".");
    if (isCurrentLight1){
        isCurrentLight1 = false;
        digitalWrite(indicatorLight1, 0);

        digitalWrite(indicatorLight2, 1);
    } else {
        isCurrentLight1 = true;
        digitalWrite(indicatorLight1, 1);

        digitalWrite(indicatorLight2, 0);
    }
}

void submittingLoop(int resultNumber, int loopNumber) {
    Serial.print("Parameter ");
    Serial.print(loopNumber);
    Serial.print(" has been set to ");
    Serial.print(resultNumber);
    Serial.println(".");

    isCurrentLight1 = false;
    digitalWrite(indicatorLight1, 1);
    digitalWrite(indicatorLight2, 1);
    delay(500);

    digitalWrite(indicatorLight1, 0);
    digitalWrite(indicatorLight2, 0);
}
