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

            bool willHitSnake(sf::Vector2i position) const;
            sf::Vector2i headPosition() const;
            std::size_t length() const;
            void length(std::size_t newLength);

        private:
            PositionList _positions;
            int _length;
            bool _keyPressed;
            bool _altSpriteIndex;

            void drawSprite(Engine *engine, sf::RenderTarget &target, sf::Vector2i position, float rotation, int index);

            static int indexOffset(bool alt);
    };
} // town