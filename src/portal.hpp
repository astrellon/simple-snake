#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace town
{
    class Engine;

    class Portal
    {
        public:
            Portal(sf::Vector2i pos1, sf::Vector2i pos2);
            ~Portal();

            sf::Vector2i pos1() const;
            sf::Vector2i pos2() const;

            void setInUse(bool inUse, float rotation);
            bool isInUse() const;

            void update(float dt);
            void draw(Engine *engine, sf::RenderTarget &target);

        private:
            sf::Vector2i _pos1;
            sf::Vector2i _pos2;
            bool _inUse;
            float _rotation;

            void drawSprite(Engine *engine, sf::RenderTarget &target, sf::Vector2i position, float rotation, int index);
    };
} // town