#pragma once
#include <SFML/Graphics.hpp>
#include "Utility.h"
#include <math.h>
#include <string>

namespace vect
{
    sf::Vector2f operator-(const sf::Vector2f& v)
    {
        return sf::Vector2f(-v.x, -v.y);
    }

    sf::Vector2f operator+(const sf::Vector2f& v)
    {
        return sf::Vector2f(+v.x, +v.y);
    }

    sf::Vector2f operator-(const sf::Vector2f& v1, const sf::Vector2f& v2)
    {
        return sf::Vector2f(v1.x - v2.x, v1.y - v2.y);
    }

    sf::Vector2f operator+(const sf::Vector2f& v1, const sf::Vector2f& v2)
    {
        return sf::Vector2f(v1.x + v2.x, v1.y + v2.y);
    }

    float operator*(const sf::Vector2f& v1, const sf::Vector2f& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    float norm(const sf::Vector2f& v)
    {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    float angle(const sf::Vector2f& v1, const sf::Vector2f& v2)
    {
        return (acos((v1 * v2) / (norm(v1) * norm(v2))) * 180.f / 3.141592653589f);
    }

    sf::Vector2f lerp(const sf::Vector2f& v1, const sf::Vector2f& v2, float t)
    {
        float x = std::lerp(v1.x, v2.x, t);
        float y = std::lerp(v1.y, v2.y, t);

        return { x, y };
    }
}
