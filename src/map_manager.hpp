#pragma once

#include <string>
#include <map>

#include "non_copyable.hpp"
#include "map.hpp"

namespace town
{
    class MapManager : private NonCopyable
    {
        public:
            Map &createMap(const std::string &mapName, uint width, uint height);
            Map *loadMap(const std::string &filename);

            typedef std::map<std::string, std::unique_ptr<Map>> MapMap;

        private:
            MapMap _maps;
    };
} // town