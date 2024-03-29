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
            const sf::Sprite *getSprite(uint index)const ;

            sf::Vector2f getSpritePosition(uint index) const;
            sf::Vector2f getSpritePosition(uint x, uint y) const;
            const sf::Texture *texture() const;

            float combinedSpriteSize() const;
            uint spriteSize() const;
            float spriteScale() const;

            std::size_t numSprites() const;

            typedef std::vector<std::unique_ptr<sf::Sprite>> SpriteList;

        private:
            const sf::Texture *_texture;
            SpriteList _sprites;
            uint _spriteSize;
            float _spriteScale;
            uint _rows;
            uint _columns;

    };
} // town