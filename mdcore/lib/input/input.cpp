#include <Arduino.h>

#include "input.h"
#include "../../include/config.h"

namespace input {
    ButtonState p1State = NONE;
    ButtonState p2State = NONE;

    ButtonState readButton(int pin) {
        int value = analogRead(pin);

        if(value < 10) {
            return NONE;
        }
        else if(value < BUTTON_UP_THRESHOLD) {
            return UP;
        }
        else if(value < BUTTON_DOWN_THRESHOLD) {
            return DOWN;
        }
        else if(value < BUTTON_LEFT_THRESHOLD) {
            return LEFT;
        }
        else if(value < BUTTON_RIGHT_THRESHOLD) {
            return RIGHT;
        }
        else if(value < BUTTON_CENTER_THRESHOLD) {
            return CENTER;
        }
        else {
            return NONE;
        }
    }

    void updateButtonStates() {
        p1State = readButton(P1_PIN);
        p2State = readButton(P2_PIN);
    }
}