#include "apple.hpp"

namespace town
{
    Apple::Apple(sf::Vector2i position) : _position(position)
    {

    }

    Apple::~Apple()
    {

    }

    sf::Vector2i Apple::position() const
    {
        return _position;
    }
} // namespace town
