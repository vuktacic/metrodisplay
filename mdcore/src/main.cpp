#include <Arduino.h>
#include "input.h"
#include "config.h"
#include "display.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32-HUB75-VirtualMatrixPanel_T.hpp>

uint32_t lastFrameMs = 0;

int lastms = 0;

void setup() {
    Serial.begin(115200);
    display::init_display();
    pong::reset_game();
}

void loop() {
    const uint32_t nowMs = millis();
    if(nowMs - lastFrameMs < FRAME_MS) {
        return;
    }

    lastFrameMs = nowMs;

    display::reset();
    
    input::updateButtonStates();
    pong::handle_input(pong::p1, input::p1State);
    pong::handle_input(pong::p2, input::p2State);

    pong::ball.move();
    pong::ball.check_collision(pong::p1, pong::p2);
    pong::Player* winner = pong::ball.check_bounds();

    if (winner != nullptr) {
        pong::iterate_game(*winner);
        display::iterate_animation(*winner);
        lastms = millis();
        return;
    }

    display::draw_paddle(pong::p1);
    display::draw_paddle(pong::p2);
    display::draw_ball(pong::ball);
    display::draw_overlay(pong::p1, pong::p2, millis() - lastms);
}
