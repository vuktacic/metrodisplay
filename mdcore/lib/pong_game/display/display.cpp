#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Arduino.h>
#include <ESP32-HUB75-VirtualMatrixPanel_T.hpp>
#include "../../include/config.h"
// #include "config.h" FUCK this shitty ass language
#include "../pong/pong.h"

namespace display {
    constexpr uint8_t NUM_ROWS = 2;
    constexpr uint8_t NUM_COLS = 2;
    constexpr uint8_t PANEL_WIDTH = 64;
    constexpr uint8_t PANEL_HEIGHT = 32;
    constexpr uint16_t PANEL_CHAIN_LENGTH = NUM_ROWS * NUM_COLS;
    constexpr uint8_t SCREEN_WIDTH = PANEL_WIDTH * NUM_COLS;


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

    void draw_paddle(const pong::Player& player) {
        virtualDisplay->fillRect(player.x, player.y, player.paddle_width, player.paddle_height, 0xFFFF);
    }

    void draw_ball(const pong::Ball& ball) {
        virtualDisplay->fillRect(ball.x, ball.y, ball.size, ball.size, 0xFFFF);
    }

    void draw_overlay(pong::Player& p1, pong::Player& p2, int timer) {
        virtualDisplay->setCursor(0, 0);
        virtualDisplay->print(p1.score);
        virtualDisplay->setCursor(SCREEN_WIDTH - 6, 0); // Assuming each digit is 6 pixels wide
        virtualDisplay->print(p2.score);
        virtualDisplay->setCursor(SCREEN_WIDTH / 2 - 12, 0); // Centered
        virtualDisplay->print(timer / 1000); // Display timer in seconds
    }

    void iterate_animation(pong::Player& winner) {
        // Simple animation: flash the screen when a player scores
        for (int i = 0; i < 3; i++) {
            display->fillScreen(0xFFFF); // White
            delay(100);
            display->fillScreen(0x0000); // Black
            delay(100);
        }

    }
}