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

    void GameSession::onResize(sf::Vector2f area)
    {
        _camera.setSize(area);
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
            auto scale = _engine->spriteScale() * 16.0f;
            auto head_position = _player.head_position();
            sf::Vector2f cam_position = sf::Vector2f(head_position.x * scale, head_position.y * scale);
            cam_position.x += 32.0f;
            cam_position.y += 32.0f;

            _camera.setCenter(cam_position);
            target.setView(_camera);

            _currentMap->draw(_engine, target);
            _player.draw(_engine, target);
        }
    }
} // namespace town
