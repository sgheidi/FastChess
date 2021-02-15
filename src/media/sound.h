#ifndef MEDIA_SOUND_H
#define MEDIA_SOUND_H

#include <SFML/Audio.hpp>

class Game_Sound {
private:
  sf::SoundBuffer buffer;
  sf::Sound sound;
public:
  Game_Sound() {
    sound.setBuffer(buffer);
  };
  void check();
  void kill();
  void error();
  void move();
};

extern Game_Sound sound;

#endif // MEDIA_SOUND_H
