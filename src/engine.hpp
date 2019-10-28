#pragma once

#include "non_copyable.hpp"
#include "font_manager.hpp"
#include "texture_manager.hpp"
#include "map_manager.hpp"
#include "tiles.hpp"
#include "snake.hpp"

#include <SFML/Graphics.hpp>

namespace town
{
    class Map;

    class Engine : private NonCopyable
    {
        public:
            Engine();
            ~Engine();

            FontManager &fontManager() const;
            TextureManager &textureManager() const;
            MapManager &mapManager() const;
            Tiles &tiles() const;

            float spriteScale() const;
            void spriteScale(float scale);

            Map *currentMap() const;
            void currentMap(Map *map);

            void readDataPaths(const std::string &filename);

            void update(float dt);
            void draw(sf::RenderTarget &target);

        private:
            mutable FontManager _fontManager;
            mutable TextureManager _textureManager;
            mutable MapManager _mapManager;
            mutable Tiles _tiles;

            Map *_currentMap;
            Snake _player;

            float _spriteScale;
    };
} // town