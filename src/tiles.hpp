#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "non_copyable.hpp"

namespace town
{
    class Tiles : private NonCopyable
    {
        public:
            void init(sf::Texture *texture, uint spriteSize);

            sf::Sprite *get_sprite(uint index);

            typedef std::vector<std::unique_ptr<sf::Sprite>> SpriteList;

        private:
            SpriteList _sprites;

    };
} // town