#pragma once
#include <Arduino.h>
#include "input.h"

namespace board {
    constexpr uint8_t SCALE = 3;
    constexpr uint8_t BOARD_WIDTH = 10;
    constexpr uint8_t BOARD_HEIGHT = 20;
    uint8_t FALL_RATE_MS = 500;
    uint8_t FAST_FALL_RATE_MS = 200;

    uint8_t lastIterationMs = 0;


    enum class Piece : uint8_t {
        I, O, T, S, Z, J, L, count
    };

    class Board {
    public:
        uint8_t score;
        Piece next_piece;
        Piece current_piece;
        int current_rotation;

        uint16_t vBoard[BOARD_HEIGHT][BOARD_WIDTH];

        int px, py;

        Board();
        void begin();
        void update(const input::ButtonState& input);

        uint8_t get_score() const {
            return score;
        }

        bool is_valid_move(int x, int y, Piece piece, int rotation);

        void new_piece();

        bool is_game_over();

        void place();

        void clear_rows();
    };
}