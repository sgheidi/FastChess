#ifndef SOUND_H
#define SOUND_H

class Game_Sound {
private:
  sf::SoundBuffer buffer;
  sf::Sound sound;
public:
  Game_Sound() {
    sound.setBuffer(buffer);
    sound.setVolume(120.f);
  };
  void error();
  void move();
};

extern Game_Sound Sound;

#endif // SOUND_H
