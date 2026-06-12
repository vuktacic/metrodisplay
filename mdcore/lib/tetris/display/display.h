#pragma once
#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32-HUB75-VirtualMatrixPanel_T.hpp>
#include "config.h"

namespace display {
    extern void init_display();
    extern void reset();
    extern void draw_board(uint8_t board[board::BOARD_HEIGHT][board::BOARD_WIDTH], uint8_t score, int x_offset);
    extern VirtualMatrixPanel_T<CHAIN_TOP_RIGHT_DOWN>* virtualDisplay;
}