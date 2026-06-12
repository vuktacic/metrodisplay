#include <Arduino.h>
#include "display/display.h"

constexpr uint32_t FRAME_MS = 33; // 30 fps

uint32_t lastFrameMs = 0;

namespace tetris {
    void init_game() {
        display::init_display();
    }

    void loop_game() {
        if(millis() - lastFrameMs < FRAME_MS) {
            return;
        }

        lastFrameMs = millis();
        display::reset();


    }
}