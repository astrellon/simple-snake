#include "map_manager.hpp"

namespace town
{
    Map &MapManager::createMap(const std::string &mapName, uint width, uint height)
    {
        const auto &find = _maps.find(mapName);
        if (find != _maps.end())
        {
            return *find->second.get();
        }

        auto map = std::make_unique<Map>(mapName, width, height);
        auto *mapPtr = map.get();
        _maps.emplace(mapName, std::move(map));

        return *mapPtr;
    }
}