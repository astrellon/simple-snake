#include "snake.hpp"

#include "engine.hpp"
#include "map.hpp"
#include "keyboard.hpp"

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
        if (Keyboard::isKeyDown(sf::Keyboard::A))
        {
            newPosition.x -= 1;
        }

        if (Keyboard::isKeyDown(sf::Keyboard::D))
        {
            newPosition.x += 1;
        }

        if (Keyboard::isKeyDown(sf::Keyboard::W))
        {
            newPosition.y -= 1;
        }

        if (Keyboard::isKeyDown(sf::Keyboard::S))
        {
            newPosition.y += 1;
        }

        if (map->canMoveTo(newPosition))
        {
            _position = newPosition;
        }
    }

    void Snake::draw(Engine *engine, sf::RenderTarget &target)
    {
        float scale = engine->spriteScale();
        const float size = 16.0f * scale;

        auto *texture = engine->textureManager().texture("snake");
        if (texture == nullptr)
        {
            return;
        }

        sf::Sprite sprite(*texture);

        sprite.setScale(sf::Vector2f(scale, scale));
        sprite.setPosition(size * _position.x, size * _position.y);
        target.draw(sprite);
    }
}