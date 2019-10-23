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
            Map &create_map(const std::string &map_name, uint width, uint height);

            typedef std::map<std::string, std::unique_ptr<Map>> MapMap;

        private:
            MapMap _maps;
    };
} // town