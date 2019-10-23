#include "map_manager.hpp"

namespace town
{
    Map &MapManager::create_map(const std::string &map_name, uint width, uint height)
    {
        const auto &find = _maps.find(map_name);
        if (find != _maps.end())
        {
            return *find->second.get();
        }

        auto map = std::make_unique<Map>(map_name, width, height);
        auto *map_ptr = map.get();
        _maps.emplace(map_name, std::move(map));

        return *map_ptr;
    }
}