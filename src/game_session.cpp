#include "game_session.hpp"

#include "map.hpp"
#include "engine.hpp"

namespace town
{
    GameSession::GameSession(Engine *engine) : _currentMap(nullptr), _engine(engine)
    {

    }
    GameSession::~GameSession()
    {

    }

    Map *GameSession::currentMap() const
    {
        return _currentMap;
    }
    void GameSession::currentMap(Map *map)
    {
        _currentMap = map;
    }

    void GameSession::update(float dt)
    {
        if (_currentMap != nullptr)
        {
            _currentMap->update(dt);
            _player.update(_currentMap, dt);
        }
    }

    void GameSession::draw(sf::RenderTarget &target)
    {
        if (_currentMap != nullptr)
        {
            _currentMap->draw(_engine, target);
            _player.draw(_engine, target);
        }
    }
} // namespace town
