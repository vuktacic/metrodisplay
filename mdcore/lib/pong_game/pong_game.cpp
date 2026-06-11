#include "input.h"
#include "config.h"
#include "./display/display.h"
#include "./pong/pong.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32-HUB75-VirtualMatrixPanel_T.hpp>

constexpr uint32_t FRAME_MS = 33; // 30 fps

uint32_t lastFrameMs = 0;

int lastms = 0;

namespace pong_game {
    void init_game() {
        display::init_display();
        pong::reset_game();
    }

    void game_loop() {
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

        if(winner != nullptr) {
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
}