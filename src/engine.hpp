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
    class GameSession;

    class Engine : private NonCopyable
    {
        public:
            Engine(sf::RenderWindow &window);
            ~Engine();

            const FontManager *fontManager() const;
            const TextureManager *textureManager() const;
            const MapManager *mapManager() const;
            const Tiles *mapTiles() const;
            const Tiles *snakeTiles() const;
            const Tiles *portalTiles() const;

            FontManager *fontManager();
            TextureManager *textureManager();
            MapManager *mapManager();
            Tiles *mapTiles();
            Tiles *snakeTiles();
            Tiles *portalTiles();

            float spriteScale() const;
            void spriteScale(float scale);

            float spriteSize() const;
            void spriteSize(float size);

            float spriteScaleCombined() const;

            sf::Vector2u windowSize() const;

            GameSession *currentSession() const;
            GameSession *startGameSession();

            void readDataPaths(const std::string &filename);

            void processEvents();
            void processEvent(const sf::Event &event);

            sf::Time deltaTime() const;
            sf::Time timeSinceStart() const;

            void preUpdate();
            void update();
            void draw();

        private:
            std::unique_ptr<FontManager> _fontManager;
            std::unique_ptr<TextureManager> _textureManager;
            std::unique_ptr<MapManager> _mapManager;
            std::unique_ptr<Tiles> _mapTiles;
            std::unique_ptr<Tiles> _snakeTiles;
            std::unique_ptr<Tiles> _portalTiles;

            float _spriteScale;
            float _spriteSize;
            std::unique_ptr<GameSession> _currentSession;
            sf::RenderWindow &_window;
            sf::Clock _timer;
            sf::Clock _timerSinceStart;
            sf::Time _deltaTime;
    };
} // town