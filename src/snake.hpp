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

            void update(Map *map, sf::Time dt);
            void draw(Engine *engine, sf::RenderTarget &target);

            typedef std::vector<sf::Vector2i> PositionList;

            sf::Vector2i head_position() const;

            std::size_t length() const;

        private:
            PositionList _positions;
            int _length;
            bool _keyPressed;
    };
} // town