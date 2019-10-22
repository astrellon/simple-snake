#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "non_copyable.hpp"
#include "vector_comparer.hpp"

namespace town
{
    class Engine;

    class Map : private NonCopyable
    {
        public:
            Map(const std::string &map_name);
            ~Map();

            const std::string &map_name() const;

            typedef std::map<sf::Vector2i, int, Vector2iComparator> MapData;

            MapData &map_data();
            const MapData &map_data() const;

            void update(float dt);
            void draw(Engine *engine, sf::RenderTarget &target);

        private:
            const std::string _map_name;
            MapData _data;
    };
} // town