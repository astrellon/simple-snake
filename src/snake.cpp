#include "snake.hpp"

#include <algorithm>
#include <iostream>

#include "engine.hpp"
#include "map.hpp"
#include "keyboard.hpp"

namespace town
{
    Snake::Snake() : _length(3)
    {
        _positions.push_back(sf::Vector2i(0, 0));
    }

    Snake::~Snake()
    {

    }

    sf::Vector2i Snake::head_position() const
    {
        return *_positions.rbegin();
    }

    void Snake::update(Map *map, float dt)
    {
        sf::Vector2i move;
        if (Keyboard::isKeyDown(sf::Keyboard::A))
        {
            move.x -= 1;
        }

        if (Keyboard::isKeyDown(sf::Keyboard::D))
        {
            move.x += 1;
        }

        if (Keyboard::isKeyDown(sf::Keyboard::W))
        {
            move.y -= 1;
        }

        if (Keyboard::isKeyDown(sf::Keyboard::S))
        {
            move.y += 1;
        }

        if (move.x != 0 || move.y != 0)
        {
            auto newPosition = *_positions.rbegin() + move;
            if (map->canMoveTo(newPosition))
            {
                if (map->hitApple(newPosition))
                {
                    _length++;
                }

                _positions.push_back(newPosition);
                if (_positions.size() > _length)
                {
                    _positions.erase(_positions.begin());
                }
            }
        }
    }

    void Snake::draw(Engine *engine, sf::RenderTarget &target)
    {
        const float scale = engine->spriteScale();
        const float size = engine->spriteSize() * scale;

        auto *texture = engine->textureManager().texture("snake");
        if (texture == nullptr)
        {
            return;
        }

        sf::Sprite sprite(*texture);

        sprite.setScale(sf::Vector2f(scale, scale));
        for (const auto &iter : _positions)
        {
            sprite.setPosition(size * iter.x, size * iter.y);
            target.draw(sprite);
        }
    }
}