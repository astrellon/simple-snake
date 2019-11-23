#pragma once

#include <string>
#include <map>

#include "../non_copyable.hpp"
#include "../map.hpp"

namespace town
{
    class Engine;

    class MapManager : private NonCopyable
    {
        public:
            MapManager(Engine *engine);

            Map &createMap(const std::string &mapName, uint width, uint height);
            Map *loadMap(const std::string &filename);

            typedef std::map<std::string, std::unique_ptr<Map>> MapMap;

        private:
            Engine *_engine;
            MapMap _maps;
    };
} // town