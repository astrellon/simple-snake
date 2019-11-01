#pragma once

#include <SFML/Graphics.hpp>

namespace town
{
    class Apple
    {
        public:
            Apple(sf::Vector2i position);
            ~Apple();

            sf::Vector2i position() const;

        private:
            sf::Vector2i _position;

    };
} // town