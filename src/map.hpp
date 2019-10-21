#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "non_copyable.hpp"

namespace town
{
    class Map : private NonCopyable
    {
        public:
            Map(const std::string &map_name);
            ~Map();

            const std::string &map_name() const;

            void update(float dt);
            void draw(sf::RenderTarget &target);

            typedef std::vector<int> MapData;

        private:
            const std::string _map_name;
            MapData _data;
    };
} // town