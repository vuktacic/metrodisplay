#include <Arduino.h>
#include "pong.h"

namespace pong {
    Player::Player(int x) {
        this->x = x;
        this->y = FIELD_HEIGHT / 2 - PADDLE_HEIGHT / 2;
        this->score = 0;
        this->paddle_height = PADDLE_HEIGHT;
        this->paddle_width = PADDLE_WIDTH;
    }

    void Player::moveUp() {
        if(y > 0) {
            y--;
        }
    }

    void Player::moveDown() {
        if(y < FIELD_HEIGHT - PADDLE_HEIGHT) {
            y++;
        }
    }

    Ball::Ball(int x, int y, int v_x, int v_y, int size) {
        this->x = x;
        this->y = y;
        this->v_x = v_x;
        this->v_y = v_y;
        this->size = size;
    }

    void Ball::move() {
        x += v_x;
        y += v_y;

        if(y <= 0 || y >= FIELD_HEIGHT - size) {
            v_y = -v_y;
        }
    }

    void Ball::check_collision(const Player& p1, const Player& p2) {
        if(x <= p1.x + PADDLE_WIDTH && y + size >= p1.y && y <= p1.y + PADDLE_HEIGHT) {
            v_x = -v_x;
            x = p1.x + PADDLE_WIDTH; // prevent sticking
        } else if(x + size >= p2.x && y + size >= p2.y && y <= p2.y + PADDLE_HEIGHT) {
            v_x = -v_x;
            x = p2.x - size; // prevent sticking
        }
    }


    Player* Ball::check_bounds() {
        if(x <= 0) {
            // p2 scores
            return &p2;
        } else if(x >= FIELD_WIDTH - size) {
            // p1 scores
            return &p1;
        }
        return nullptr; // no winner
    }

    Player p1 = Player(0);
    Player p2 = Player(FIELD_WIDTH - PADDLE_WIDTH);

    Ball ball = Ball(FIELD_WIDTH / 2 - BALL_SIZE / 2, FIELD_HEIGHT / 2 - BALL_SIZE / 2, 1, 1, BALL_SIZE);

    void reset_game() {
        p1.y = FIELD_HEIGHT / 2 - PADDLE_HEIGHT / 2;
        p1.score = 0;

        p2.y = FIELD_HEIGHT / 2 - PADDLE_HEIGHT / 2;
        p2.score = 0;

        ball = Ball(FIELD_WIDTH / 2 - BALL_SIZE / 2, FIELD_HEIGHT / 2 - BALL_SIZE / 2, 1, 1, BALL_SIZE);
    }

    void iterate_game(Player& winner) {
        p1.y = FIELD_HEIGHT / 2 - PADDLE_HEIGHT / 2;
        p2.y = FIELD_HEIGHT / 2 - PADDLE_HEIGHT / 2;

        winner.score++;

        ball = Ball(FIELD_WIDTH / 2 - BALL_SIZE / 2, FIELD_HEIGHT / 2 - BALL_SIZE / 2, winner.x < FIELD_WIDTH / 2 ? 1 : -1, 1, BALL_SIZE);
    }

    void handle_input(Player& player, input::ButtonState state) {
        if(state == input::ButtonState::UP) {
            player.moveUp();
        } else if(state == input::ButtonState::DOWN) {
            player.moveDown();
        }
    }
}