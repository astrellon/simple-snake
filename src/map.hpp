#pragma once

#include <map>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "non_copyable.hpp"
#include "vector_comparer.hpp"

namespace town
{
    class Map : private NonCopyable
    {
        public:
            Map(const std::string &map_name);
            ~Map();

            const std::string &map_name() const;

            typedef std::unordered_map<sf::Vector2i, int> MapData;

            MapData &map_data();
            const MapData &map_data() const;

            void update(float dt);
            void draw(sf::RenderTarget &target);

        private:
            const std::string _map_name;
            MapData _data;
    };
} // town