#include "engine.hpp"

#include <iostream>
#include <fstream>

#include "utils.hpp"
#include "map.hpp"
#include "game_session.hpp"

namespace town
{
    Engine::Engine() : _spriteScale(1.0f)
    {

    }
    Engine::~Engine()
    {

    }

    FontManager &Engine::fontManager() const
    {
        return _fontManager;
    }

    TextureManager &Engine::textureManager() const
    {
        return _textureManager;
    }

    MapManager &Engine::mapManager() const
    {
        return _mapManager;
    }

    Tiles &Engine::tiles() const
    {
        return _tiles;
    }

    float Engine::spriteScale() const
    {
        return _spriteScale;
    }
    void Engine::spriteScale(float scale)
    {
        _spriteScale = scale;
    }

    GameSession *Engine::currentSession() const
    {
        return _currentSession.get();
    }
    GameSession *Engine::startGameSession()
    {
        _currentSession = std::make_unique<GameSession>(this);
        return _currentSession.get();
    }

    void Engine::readDataPaths(const std::string &filename)
    {
        Utils::readCSVLines(filename, [=](const std::string &line)
        {
            auto tokens = Utils::split(line, ',', true);
            if (tokens[0] == "font")
            {
                _fontManager.load_font(tokens[1], "data/" + tokens[2]);
            }
            else if (tokens[0] == "texture")
            {
                _textureManager.loadTexture(tokens[1], "data/" + tokens[2]);
            }
            else
            {
                std::cout << "Unknown data path line: " << line << std::endl;
            }

            return true;
        });
    }

    void Engine::update(float dt)
    {
        if (_currentSession.get())
        {
            _currentSession->update(dt);
        }
    }

    void Engine::draw(sf::RenderTarget &target)
    {
        if (_currentSession.get())
        {
            _currentSession->draw(target);
        }
    }
}