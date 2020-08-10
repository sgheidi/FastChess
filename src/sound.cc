#include "../include/common.h"

void Game_Sound::error() {
  buffer.loadFromFile("assets/error.wav");
  sound.play();
}

void Game_Sound::move() {
  buffer.loadFromFile("assets/move.wav");
  sound.play();
}
