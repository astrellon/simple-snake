#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "non_copyable.hpp"
#include "vector_comparer.hpp"
#include "apple.hpp"

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
            typedef std::vector<Apple> AppleList;

            MapData &mapData();
            const MapData &mapData() const;
            uint width() const;
            uint height() const;

            void tile(int x, int y, int tile);
            int tile(int x, int y) const;

            bool canMoveTo(sf::Vector2i position) const;
            bool hitApple(sf::Vector2i position);

            void update(Engine *engine, sf::Time dt);
            void draw(Engine *engine, sf::RenderTarget &target);

        private:
            const std::string _mapName;
            uint _width;
            uint _height;
            MapData _data;
            AppleList _apples;

    };
} // town