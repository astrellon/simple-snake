#pragma once

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

        private:
            sf::Vector2i _position;
            bool _keyPressed;
    };
} // town