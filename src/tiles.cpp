#include "tiles.hpp"

namespace town
{
    void Tiles::init(const sf::Texture *texture, uint spriteSize)
    {
        auto size = texture->getSize();
        auto rows = size.y / spriteSize;
        auto columns = size.x / spriteSize;

        for (auto y = 0; y < columns; y++)
        {
            for (auto x = 0; x < rows; x++)
            {
                auto rect = sf::IntRect(x * spriteSize, y * spriteSize, spriteSize, spriteSize);
                _sprites.push_back(std::make_unique<sf::Sprite>(*texture, rect));
            }
        }
    }

    sf::Sprite *Tiles::get_sprite(uint index)
    {
        if (_sprites.size() <= index)
        {
            return nullptr;
        }

        return _sprites[index].get();
    }
}