#pragma once

#include "managers/font_manager.hpp"
#include "managers/texture_manager.hpp"
#include "managers/map_manager.hpp"
#include "managers/particle_manager.hpp"
#include "managers/tiles_manager.hpp"
#include "tiles.hpp"
#include "snake.hpp"
#include "non_copyable.hpp"

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
            const ParticleManager *particleManager() const;
            const TilesManager *tilesManager() const;

            FontManager *fontManager();
            TextureManager *textureManager();
            MapManager *mapManager();
            ParticleManager *particleManager();
            TilesManager *tilesManager();

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
            std::unique_ptr<ParticleManager> _particleManager;
            std::unique_ptr<TilesManager> _tilesManager;

            float _spriteScale;
            float _spriteSize;
            std::unique_ptr<GameSession> _currentSession;
            sf::RenderWindow &_window;
            sf::Clock _timer;
            sf::Clock _timerSinceStart;
            sf::Time _deltaTime;
    };
} // town