#include "Utility.h"

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
        return acos((v1 * v2) / (norm(v1) * norm(v2)));
    }
}