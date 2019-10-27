#include "snake.hpp"

#include "engine.hpp"
#include "map.hpp"

namespace town
{
    Snake::Snake()
    {

    }

    Snake::~Snake()
    {

    }

    void Snake::update(Map *map, float dt)
    {
        sf::Vector2i newPosition = _position;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            newPosition.x -= 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            newPosition.x += 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            newPosition.y -= 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            newPosition.y += 1;
        }

        auto onTile = map->tile(newPosition.x, newPosition.y);
        if (onTile < 8 && onTile >= 0)
        {
            _position = newPosition;
        }
    }

    void Snake::draw(Engine *engine, sf::RenderTarget &target)
    {
        const float size = 64;
        auto *texture = engine->textureManager().texture("snake");
        if (texture == nullptr)
        {
            return;
        }

        sf::Sprite sprite(*texture);

        sprite.setScale(sf::Vector2f(4.f, 4.f));
        sprite.setPosition(size * _position.x, size * _position.y);
        target.draw(sprite);
    }
}