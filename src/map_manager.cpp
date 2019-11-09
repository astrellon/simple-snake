#include "map_manager.hpp"

#include <iostream>

#include "engine.hpp"
#include "utils.hpp"

namespace town
{
    MapManager::MapManager(Engine *engine) : _engine(engine)
    {

    }

    Map &MapManager::createMap(const std::string &mapName, uint width, uint height)
    {
        const auto &find = _maps.find(mapName);
        if (find != _maps.end())
        {
            return *find->second.get();
        }

        auto map = std::make_unique<Map>(_engine, mapName, width, height);
        auto *mapPtr = map.get();
        _maps.emplace(mapName, std::move(map));

        return *mapPtr;
    }

    Map *MapManager::loadMap(const std::string &filename)
    {
        std::string mapName;
        int width, height;
        int y = 0;

        Utils::readCSVLines(filename, [&width, &height, &mapName] (const std::string &line) mutable
        {
            auto tokens = Utils::split(line, ',', true);
            if (tokens[0] == "info")
            {
                mapName = tokens[1];
                width = std::stoi(tokens[2]);
                height = std::stoi(tokens[3]);
                return false;
            }

            return true;
        });

        if (mapName.size() == 0)
        {
            std::cout << "Error loading map " << filename << std::endl;
            return nullptr;
        }

        auto &map = createMap(mapName, width, height);

        Utils::readCSVLines(filename, [&y, &map] (const std::string &line) mutable
        {
            auto tokens = Utils::split(line, ',', true);
            if (tokens[0] == "row")
            {
                for (int x = 1; x < tokens.size(); x++)
                {
                    auto tile = std::stoi(tokens[x]);
                    map.tile(x - 1, y, tile);
                }
                y++;
            }
            else if (tokens[0] == "portal")
            {
                auto x1 = std::stoi(tokens[1]);
                auto y1 = std::stoi(tokens[2]);
                auto x2 = std::stoi(tokens[3]);
                auto y2 = std::stoi(tokens[4]);

                map.addPortal(sf::Vector2i(x1, y1), sf::Vector2i(x2, y2));
            }

            return true;
        });

        return &map;
    }
}