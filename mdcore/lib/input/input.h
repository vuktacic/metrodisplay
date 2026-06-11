#pragma once

namespace input {
    enum ButtonState {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        CENTER
    };

    extern ButtonState p1State;
    extern ButtonState p2State;

    ButtonState readButton(int pin);

    void updateButtonStates();
}