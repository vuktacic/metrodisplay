#include <Arduino.h>
#include "board.h"

namespace board {
    Board::Board() {
        this->score = 0;
        this->px = BOARD_WIDTH / 2 - 1;
        this->py = 0;
    }

    void Board::begin() {
        memset(board, 0, sizeof(board));
        lastIterationMs = millis();
    }

    void Board::new_piece() {
        randomSeed(analogRead(1));
        this->current_piece = this->next_piece;
        this->next_piece = static_cast<Piece>(random(0, 7));

        this->px = BOARD_WIDTH / 2 - 1;
        this->py = 0;
    }

    void Board::update(const input::ButtonState& input) {
        if(input == input::LEFT) {
            if(px > 0) {
                px--;
            }
        }

        if(input == input::RIGHT) {
            if(px < BOARD_WIDTH - 1) {
                px++;
            }
        }

        if(input == input::UP) {
            // TODO: rotate piece
        }

        if(input == input::CENTER) {
            // TODO: hard drop
        }

        const uint8_t fall_rate = (input == input::DOWN) ? FAST_FALL_RATE_MS : FALL_RATE_MS;
        if(millis() - lastIterationMs > fall_rate) {
            py++;
            lastIterationMs = millis();
        }
    }
}