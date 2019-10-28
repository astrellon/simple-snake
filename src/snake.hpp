#pragma once

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace town
{
    class Engine;
    class Map;

    class Snake
    {
        public:
            Snake();
            ~Snake();

            void update(Map *map, float dt);
            void draw(Engine *engine, sf::RenderTarget &target);

            typedef std::vector<sf::Vector2i> PositionList;

        private:
            PositionList _positions;
            int _length;
            bool _keyPressed;
    };
} // town