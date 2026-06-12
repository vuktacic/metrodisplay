#include <Arduino.h>
#include "display/display.h"
#include "board/board.h"

constexpr uint32_t FRAME_MS = 33; // 30 fps

uint32_t lastFrameMs = 0;

board::Board board1;

namespace tetris {
    void init_game() {
        display::init_display();
        board1 = board::Board();
        board1.begin();
    }

    void loop_game() {
        if(millis() - lastFrameMs < FRAME_MS) {
            input::updateButtonStates();
            return;
        }

        lastFrameMs = millis();

        board1.update(input::p1State);
        board1.clear_rows();

        if(board1.is_game_over()) {
            display::draw_game_over(board1.score);
            delay(3000);
            return;
        }






        display::reset();
        display::draw_board(board1.vBoard, board1.score, 2);
    }
}