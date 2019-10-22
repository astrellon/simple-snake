#include "map.hpp"

#include <SFML/Graphics.hpp>

#include "engine.hpp"

namespace town
{
    Map::Map(const std::string &map_name) : _map_name(map_name)
    {

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

    void Map::update(float dt)
    {

    }

    void Map::draw(Engine *engine, sf::RenderTarget &target)
    {
        const float size = 64;

        for (const auto &iter : _data)
        {
            auto *sprite = engine->tiles().get_sprite(iter.second);
            if (sprite == nullptr)
            {
                continue;
            }
            sprite->setScale(sf::Vector2f(4.f, 4.f));
            sprite->setPosition(size * iter.first.x, size * iter.first.y);
            target.draw(*sprite);
        }
    }
}