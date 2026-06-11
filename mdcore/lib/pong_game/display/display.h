#pragma once
#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32-HUB75-VirtualMatrixPanel_T.hpp>
#include "config.h"
#include "../pong/pong.h"

namespace display {
    extern void init_display();
    extern void reset();
    extern void draw_paddle(const pong::Player& player);
    extern void draw_ball(const pong::Ball& ball);
    extern VirtualMatrixPanel_T<CHAIN_TOP_RIGHT_DOWN>* virtualDisplay;
    extern void draw_overlay(pong::Player& p1, pong::Player& p2, int timer);
    extern void iterate_animation(pong::Player& winner);
}