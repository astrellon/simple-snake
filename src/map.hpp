#pragma once

#include <vector>
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
            Map(const std::string &map_name, uint width, uint height);
            ~Map();

            const std::string &map_name() const;

            typedef std::vector<int> MapData;

            MapData &map_data();
            const MapData &map_data() const;
            uint width() const;
            uint height() const;

            void update(float dt);
            void draw(Engine *engine, sf::RenderTarget &target);

        private:
            const std::string _map_name;
            uint _width;
            uint _height;
            MapData _data;
    };
} // town