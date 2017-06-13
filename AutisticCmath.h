#pragma once
#include <SFML\Graphics.hpp>
#include <cmath>

const float EPSILON = 0.01f;
inline float abs_f(float);

inline sf::Vector2f crossVS(const sf::Vector2f &v, float a);
inline sf::Vector2f crossSV(float a, const sf::Vector2f &v);
inline float crossVV(const sf::Vector2f &a, const sf::Vector2f &b);

inline float dot(const sf::Vector2f &a, const sf::Vector2f &b);

inline float vecLenght(const sf::Vector2f &a);
inline float vecLenghtSq(const sf::Vector2f &a);
inline sf::Vector2f vecNormalize(sf::Vector2f &a);
inline float distance(const sf::Vector2f &a, const sf::Vector2f &b);
inline float distanceSq(const sf::Vector2f & a, const sf::Vector2f & b);

inline bool equal(float a, float b);
inline float sqr(float a);

inline bool BiasGreaterThan(float a, float b);
