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

    Snake &GameSession::player()
    {
        return _player;
    }

    void GameSession::onResize(sf::Vector2f area)
    {
        _camera.setSize(area);
    }

    void GameSession::update(sf::Time dt)
    {
        if (_currentMap != nullptr)
        {
            _currentMap->update(_engine, dt);
            _player.update(_currentMap, dt);
        }
    }

    void GameSession::draw(sf::RenderTarget &target)
    {
        if (_currentMap != nullptr)
        {
            auto scale = _engine->spriteScale() * _engine->spriteSize();
            auto head_position = _player.headPosition();
            sf::Vector2f cam_position = sf::Vector2f(_currentMap->width() * scale * 0.5f, _currentMap->height() * scale * 0.5f);

            _camera.setCenter(cam_position);
            target.setView(_camera);

            _currentMap->draw(_engine, target);
            _player.draw(_engine, target);
        }
    }
} // namespace town
