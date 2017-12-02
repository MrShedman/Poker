#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include <sstream>

template <class T>
void clamp(T &value, T min, T max);

template <class T>
bool outOfRange(T value, T min, T max);

template <class T>
std::string toString(const T& value);

extern std::vector<sf::VideoMode> getValidVideoModes();

extern sf::Vector2f getMousePosition(const sf::RenderWindow &window);

extern sf::View getAlignedView(sf::View view);

extern void	centreOrigin(sf::Sprite& sprite);

extern void	centreOrigin(sf::Text& text);

extern void centreSpriteToWindow(sf::Sprite &sprite, const sf::RenderWindow &window, sf::Vector2f offset = { 0.f, 0.f });

extern void scaleSpriteToFitWindow(sf::Sprite &sprite, const sf::RenderWindow &window);

extern float randomize(float min, float max);

extern int randomize(int min, int max);

extern float length(sf::Vector2f vector);

#include <Utility.inl>