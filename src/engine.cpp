#include "engine.hpp"

#include <iostream>
#include <fstream>

#include "utils.hpp"
#include "map.hpp"
#include "game_session.hpp"
#include "keyboard.hpp"

namespace town
{
    Engine::Engine(sf::RenderWindow &window) :
        _spriteScale(1.0f), _spriteSize(16.0f), _window(window), _deltaTime(sf::Time::Zero)
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

    float Engine::spriteSize() const
    {
        return _spriteSize;
    }
    void Engine::spriteSize(float size)
    {
        _spriteSize = size;
    }

    float Engine::spriteScaleCombined() const
    {
        return _spriteSize * _spriteScale;
    }

    sf::Vector2u Engine::windowSize() const
    {
        return _window.getSize();
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

    void Engine::processEvents()
    {
        sf::Event event;
        Keyboard::resetKeys();

        while (_window.pollEvent(event))
        {
            processEvent(event);
        }
    }

    void Engine::processEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::Closed)
        {
            _window.close();
        }
        // catch the resize events
        else if (event.type == sf::Event::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            _window.setView(sf::View(visibleArea));

            if (_currentSession.get() != nullptr)
            {
                sf::Vector2f area(event.size.width, event.size.height);
                _currentSession->onResize(area);
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            Keyboard::setKeyDown(event.key.code);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            Keyboard::setKeyUp(event.key.code);
        }
    }

    const sf::Time Engine::deltaTime() const
    {
        return _deltaTime;
    }

    void Engine::preUpdate()
    {
        _deltaTime = _timer.getElapsedTime();
        _timer.restart();
    }

    void Engine::update()
    {
        if (_currentSession.get())
        {
            _currentSession->update(_deltaTime);
        }
    }

    void Engine::draw()
    {
        _window.clear();
        if (_currentSession.get())
        {
            _currentSession->draw(_window);
        }
        _window.display();
    }
}