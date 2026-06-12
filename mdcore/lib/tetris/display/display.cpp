#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Arduino.h>
#include <ESP32-HUB75-VirtualMatrixPanel_T.hpp>
#include "../../include/config.h"
#include "board/board.h"
// #include "config.h" FUCK this shitty ass language

namespace display {
    constexpr uint8_t NUM_ROWS = 2;
    constexpr uint8_t NUM_COLS = 2;
    constexpr uint8_t PANEL_WIDTH = 64;
    constexpr uint8_t PANEL_HEIGHT = 32;
    constexpr uint16_t PANEL_CHAIN_LENGTH = NUM_ROWS * NUM_COLS;
    constexpr uint8_t SCREEN_WIDTH = PANEL_WIDTH * NUM_COLS;
    constexpr uint8_t SCREEN_HEIGHT = PANEL_HEIGHT * NUM_ROWS;


    MatrixPanel_I2S_DMA* display = nullptr;

    VirtualMatrixPanel_T<CHAIN_TOP_RIGHT_DOWN>* virtualDisplay = nullptr;



    HUB75_I2S_CFG::i2s_pins pins = {
        R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN,
        A_PIN, B_PIN, C_PIN, D_PIN, E_PIN,
        LAT_PIN, OE_PIN, CLK_PIN
    };

    HUB75_I2S_CFG cfg(
        PANEL_WIDTH,
        PANEL_HEIGHT,
        PANEL_CHAIN_LENGTH,
        pins
    );

    void init_display() {
        display = new MatrixPanel_I2S_DMA(cfg);
        display->begin();
        display->setBrightness(64);
        display->clearScreen();

        virtualDisplay = new VirtualMatrixPanel_T<CHAIN_TOP_RIGHT_DOWN>(NUM_ROWS, NUM_COLS, PANEL_WIDTH, PANEL_HEIGHT);
        virtualDisplay->setDisplay(*display);
    }

    void reset() {
        display->clearScreen();
    }

    void draw_board(uint8_t board[board::BOARD_HEIGHT][board::BOARD_WIDTH], uint8_t score, int x_offset) {
        for(int y = 0; y < board::BOARD_HEIGHT; y++) {
            for(int x = 0; x < board::BOARD_WIDTH; x++) {
                // value of cell IS the colour, and we need to scale by size
                uint16_t colour = board[y][x];
                virtualDisplay->fillRect(x * board::SCALE + x_offset, y * board::SCALE + 1, board::SCALE, board::SCALE, colour);
            }
        }

        virtualDisplay->setCursor(SCREEN_WIDTH / 2, x_offset * 3);
        virtualDisplay->setTextColor(virtualDisplay->color565(255, 255, 255));
        virtualDisplay->setTextSize(1);
        virtualDisplay->print(score);
    }

    void draw_game_over(uint8_t score) {
        virtualDisplay->fillScreen(virtualDisplay->color565(0, 0, 0));
        virtualDisplay->setCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 10);
        virtualDisplay->setTextColor(virtualDisplay->color565(255, 0, 0));
        virtualDisplay->setTextSize(2);
        virtualDisplay->print("GAME OVER");
        virtualDisplay->setCursor(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 10);
        virtualDisplay->setTextColor(virtualDisplay->color565(255, 255, 255));
        virtualDisplay->setTextSize(1);
        virtualDisplay->print("SCORE: ");
        virtualDisplay->print(score);
    }
}