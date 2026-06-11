#pragma once
#include <Arduino.h>
#include "input.h"

constexpr int PADDLE_HEIGHT = 16;
constexpr int PADDLE_WIDTH = 4;
constexpr int FIELD_WIDTH = 128;
constexpr int FIELD_HEIGHT = 64;
constexpr int BALL_SIZE = 2;

namespace pong {
    class Player {
    public:
        int y;
        int x;
        int score;
        int paddle_height;
        int paddle_width;

        explicit Player(int x);

        void moveUp();

        void moveDown();
    };



    class Ball {
    public:
        int x;
        int y;
        int v_x;
        int v_y;
        int size;

        explicit Ball(int x, int y, int v_x, int v_y, int size);

        void move();
        void check_collision(const Player& p1, const Player& p2);
        Player* check_bounds();
    };

    extern Player p1;
    extern Player p2;
    extern Ball ball;

    extern void reset_game();
    extern void iterate_game(Player& winner);

    extern void handle_input(Player& player, input::ButtonState state);
}