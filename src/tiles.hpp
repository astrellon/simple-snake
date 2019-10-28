#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "non_copyable.hpp"

namespace town
{
    class Tiles : private NonCopyable
    {
        public:
            void init(const sf::Texture *texture, uint spriteSize, float spriteScale);

            sf::Sprite *getSprite(uint index);

            typedef std::vector<std::unique_ptr<sf::Sprite>> SpriteList;

        private:
            SpriteList _sprites;

    };
} // town