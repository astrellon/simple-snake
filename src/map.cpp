#include "map.hpp"

#include <SFML/Graphics.hpp>

#include "engine.hpp"

namespace town
{
    Map::Map(const std::string &map_name, uint width, uint height) :
        _map_name(map_name), _width(width), _height(height)
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

    const std::string &Map::map_name() const
    {
        return _map_name;
    }

    Map::MapData &Map::map_data()
    {
        return _data;
    }

    const Map::MapData &Map::map_data() const
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

    void Map::update(float dt)
    {

    }

    void Map::draw(Engine *engine, sf::RenderTarget &target)
    {
        const float size = 64;

        auto x = 0, y = 0;
        for (const auto tile : _data)
        {
            auto *sprite = engine->tiles().get_sprite(tile);
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