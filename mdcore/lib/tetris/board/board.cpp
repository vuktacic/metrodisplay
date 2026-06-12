#include <Arduino.h>
#include "board.h"
#include "pieces.h"
#include "display/display.h"

namespace board {
    Board::Board() {
        this->score = 0;
        this->px = BOARD_WIDTH / 2 - 1;
        this->py = 0;
        this->current_rotation = 0;
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
            if(px > 0 && is_valid_move(px - 1, py, current_piece, current_rotation)) {
                px--;
            }
        }

        if(input == input::RIGHT) {
            if(px < BOARD_WIDTH - 1 && is_valid_move(px + 1, py, current_piece, current_rotation)) {
                px++;
            }
        }

        if(input == input::UP && is_valid_move(px, py, current_piece, (current_rotation + 1) % 4)) {
            // TODO: rotate piece
        }

        if(input == input::CENTER) {
            // TODO: hard drop
        }

        const uint8_t fall_rate = (input == input::DOWN) ? FAST_FALL_RATE_MS : FALL_RATE_MS;
        if(millis() - lastIterationMs > fall_rate) {

            if(is_valid_move(px, py + 1, current_piece, current_rotation)) {
                py++;
            } else {
                place();
                new_piece();
            }

            lastIterationMs = millis();
        }
    }

    bool Board::is_valid_move(int x, int y, Piece piece, int rotation) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if((board::PIECES[static_cast<size_t>(piece)][rotation][i] >> (3 - j)) & 1) {
                    int new_x = x + j;
                    int new_y = y + i;

                    if(new_x < 0 || new_x >= BOARD_WIDTH || new_y < 0 || new_y >= BOARD_HEIGHT) {
                        return false;
                    }

                    if(board[new_y][new_x] != 0) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool Board::is_game_over() {
        return false;
    }

    void Board::place() {
        // map array of bit values from pieces.h to white on the board array.
        const uint16_t colour = display::virtualDisplay->color565(255, 255, 255);

        /* {{
            0b0000,
            0b1111,
            0b0000,
            0b0000
        },
        */

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if((board::PIECES[static_cast<size_t>(current_piece)][current_rotation][i] >> (3 - j)) & 1) {
                    int new_x = px + j;
                    int new_y = py + i;

                    if(new_x >= 0 && new_x < BOARD_WIDTH && new_y >= 0 && new_y < BOARD_HEIGHT) {
                        board[new_y][new_x] = colour;
                    }
                }
            }
        }
    }
}