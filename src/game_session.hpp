#pragma once

#include <SFML/Graphics.hpp>

#include "snake.hpp"

namespace town
{
    class Map;
    class Engine;

    class GameSession
    {
        public:
            GameSession(Engine *engine);
            ~GameSession();

            Map *currentMap() const;
            void currentMap(Map *map);

            void onResize(sf::Vector2f area);

            void update(float dt);
            void draw(sf::RenderTarget &target);

        private:
            Map *_currentMap;
            Engine *_engine;
            Snake _player;
            sf::View _camera;
    };
} // town