#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Arduino.h>
#include <ESP32-HUB75-VirtualMatrixPanel_T.hpp>
#include "../../include/config.h"
// #include "config.h" FUCK this shitty ass language

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
}