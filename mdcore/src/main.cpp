#include <Arduino.h>
#include "pong_game.h"

void setup() {
    Serial.begin(115200);
    pong_game::init_game();
}

void loop() {
    pong_game::game_loop();
}
