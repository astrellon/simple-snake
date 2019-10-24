#include "map.hpp"

#include <SFML/Graphics.hpp>

#include "engine.hpp"

namespace town
{
    Map::Map(const std::string &mapName, uint width, uint height) :
        _mapName(mapName), _width(width), _height(height)
    {
        _data.resize(width * height);
        for (auto i = 0; i < width * height; i++)
        {
            _data[i] = 0;
        }
    }

    Map::~Map()
    {

    }

    const std::string &Map::mapName() const
    {
        return _mapName;
    }

    Map::MapData &Map::mapData()
    {
        return _data;
    }

    const Map::MapData &Map::mapData() const
    {
        return _data;
    }

    uint Map::width() const
    {
        return _width;
    }

    uint Map::height() const
    {
        return _height;
    }

    void Map::setTile(uint x, uint y, int tile)
    {
        auto index = y * _width + x;
        if (index < _data.size())
        {
            _data[index] = tile;
        }
    }

    void Map::update(float dt)
    {

    }

    void Map::draw(Engine *engine, sf::RenderTarget &target)
    {
        const float size = 64;

        auto x = 0, y = 0;
        for (const auto tile : _data)
        {
            auto *sprite = engine->tiles().getSprite(tile);
            if (sprite == nullptr)
            {
                continue;
            }

            sprite->setScale(sf::Vector2f(4.f, 4.f));
            sprite->setPosition(size * x, size * y);
            target.draw(*sprite);

            x++;
            if (x >= _width)
            {
                y++;
                x = 0;
            }
        }
    }
}