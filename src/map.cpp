#include "map.hpp"

#include <SFML/Graphics.hpp>

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

    void Map::draw(sf::RenderTarget &target)
    {
        sf::RectangleShape tile;
        tile.setSize(sf::Vector2f(50, 50));
        tile.setFillColor(sf::Color::Red);

        for (const auto &iter : _data)
        {
            tile.setPosition(50.0f * iter.first.x, 50.0f * iter.first.y);
            target.draw(tile);
        }
    }
}