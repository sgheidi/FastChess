#include "../include/common.h"

void Game_Sound::kill() {
  buffer.loadFromFile("assets/kill.wav");
  sound.setVolume(120.f);
  sound.play();
}

void Game_Sound::error() {
  buffer.loadFromFile("assets/error.wav");
  sound.setVolume(120.f);
  sound.play();
}

void Game_Sound::move() {
  buffer.loadFromFile("assets/move.wav");
  sound.setVolume(120.f);
  sound.play();
}
