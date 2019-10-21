#include "map.hpp"

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

    void Map::update(float dt)
    {

    }

    void Map::draw(sf::RenderTarget &target)
    {

    }
}