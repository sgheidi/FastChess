#include <iostream>

#include "../common/config.h"
#include "text.h"

void Game_Text::checkmate() {
  text.setFont(font);
  text.setString("Checkmate");
  text.setCharacterSize(40);
  text.setFillColor(sf::Color(color[0], color[1], color[2]));
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  text.setPosition(sf::Vector2f(X_RES/2.0f,Y_RES/2.0f));
  window.draw(text);
}

void Game_Text::stalemate() {
  text.setFont(font);
  text.setString("Stalemate");
  text.setCharacterSize(40);
  text.setFillColor(sf::Color(color[0], color[1], color[2]));
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  text.setPosition(sf::Vector2f(X_RES/2.0f,Y_RES/2.0f));
  window.draw(text);
}
