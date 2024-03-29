#include "tiles.hpp"

#include "engine.hpp"

namespace town
{
    void Tiles::init(const sf::Texture *texture, uint spriteSize, float spriteScale)
    {
        _texture = texture;

        auto size = texture->getSize();
        _rows = size.y / spriteSize;
        _columns = size.x / spriteSize;

        _spriteSize = spriteSize;
        _spriteScale = spriteScale;

        for (auto y = 0; y < _columns; y++)
        {
            for (auto x = 0; x < _rows; x++)
            {
                auto rect = sf::IntRect(x * spriteSize, y * spriteSize, spriteSize, spriteSize);

                auto sprite = std::make_unique<sf::Sprite>(*texture, rect);
                sprite->setScale(spriteScale, spriteScale);

                _sprites.push_back(std::move(sprite));
            }
        }
    }

    sf::Sprite *Tiles::getSprite(uint index)
    {
        if (_sprites.size() <= index)
        {
            return nullptr;
        }

        return _sprites[index].get();
    }

    const sf::Sprite *Tiles::getSprite(uint index) const
    {
        if (_sprites.size() <= index)
        {
            return nullptr;
        }

        return _sprites[index].get();
    }

    sf::Vector2f Tiles::getSpritePosition(uint index) const
    {
        if (_sprites.size() <= index)
        {
            return sf::Vector2f(0, 0);
        }

        auto x = index % _columns;
        auto y = index / _rows;

        return sf::Vector2f(x * _spriteSize, y * _spriteSize);
    }

    sf::Vector2f Tiles::getSpritePosition(uint x, uint y) const
    {
        return sf::Vector2f(x * _spriteSize, y * _spriteSize);
    }

    const sf::Texture *Tiles::texture() const
    {
        return _texture;
    }

    float Tiles::combinedSpriteSize() const
    {
        return _spriteSize * _spriteScale;
    }
    uint Tiles::spriteSize() const
    {
        return _spriteSize;
    }
    float Tiles::spriteScale() const
    {
        return _spriteScale;
    }

    std::size_t Tiles::numSprites() const
    {
        return _sprites.size();
    }
}