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
            Map(const std::string &mapName, uint width, uint height);
            ~Map();

            const std::string &mapName() const;

            typedef std::vector<int> MapData;

            MapData &mapData();
            const MapData &mapData() const;
            uint width() const;
            uint height() const;

            void tile(uint x, uint y, int tile);
            int tile(uint x, uint y);

            void update(float dt);
            void draw(Engine *engine, sf::RenderTarget &target);

        private:
            const std::string _mapName;
            uint _width;
            uint _height;
            MapData _data;
    };
} // town