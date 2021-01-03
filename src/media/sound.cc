#include <iostream>

#include "sound.h"

void Game_Sound::check() {
  buffer.loadFromFile("assets/check.wav");
  sound.setVolume(100.f);
  sound.setPlayingOffset(sf::milliseconds(95));
  sound.play();
}

void Game_Sound::kill() {
  buffer.loadFromFile("assets/kill.wav");
  sound.setVolume(100.f);
  sound.setPlayingOffset(sf::milliseconds(95));
  sound.play();
}

void Game_Sound::error() {
  buffer.loadFromFile("assets/error.wav");
  sound.setVolume(500.f);
  sound.play();
}

void Game_Sound::move() {
  buffer.loadFromFile("assets/move.wav");
  sound.setVolume(100.f);
  sound.play();
}
