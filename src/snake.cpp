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

    std::size_t Snake::length() const
    {
        return _positions.size();
    }

    void Snake::update(Map *map, sf::Time dt)
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
        const float size = engine->spriteSize();
        const float combinedScale = engine->spriteScaleCombined();
        const sf::Vector2f halfSize(size * 0.5f, size * 0.5f);

        /*
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
        */

        if (_positions.size() == 1)
        {
            auto sprite = engine->snakeTiles().getSprite(0);
            const auto &pos = _positions[0];
            sprite->setPosition(pos.x * combinedScale, pos.y * combinedScale);
            target.draw(*sprite);
        }
        else
        {
            {
                auto tailPos = _positions[0];
                auto nextPos = _positions[1];
                auto diff = nextPos - tailPos;
                auto tailSprite = engine->snakeTiles().getSprite(1);

                auto pos = (sf::Vector2f(tailPos) * combinedScale) + (halfSize * scale);
                tailSprite->setOrigin(halfSize);
                tailSprite->setPosition(pos);

                if (diff.y == 0)
                {
                    tailSprite->setRotation(diff.x < 0 ? 180 : 0);
                }
                else
                {
                    tailSprite->setRotation(diff.y < 0 ? 270 : 90);
                }
                target.draw(*tailSprite);
            }

            for (auto i = 1; i < _positions.size() - 1; i++)
            {
                const auto &prevPos = _positions[i - 1];
                const auto &pos = _positions[i];
                const auto &nextPos = _positions[i + 1];

                auto prevDiff = pos - prevPos;
                auto nextDiff = nextPos - pos;
                auto index = prevDiff == nextDiff ? 2 : 4;

                auto middleSprite = engine->snakeTiles().getSprite(index);

                auto drawPos = (sf::Vector2f(pos) * combinedScale) + (halfSize * scale);
                middleSprite->setOrigin(halfSize);
                middleSprite->setPosition(drawPos);

                auto rotation = 0.0f;

                if (index == 2)
                {
                    if (prevDiff.y == 0)
                    {
                        rotation = prevDiff.x < 0 ? 180 : 0;
                    }
                    else
                    {
                        rotation = prevDiff.y < 0 ? 270 : 90;
                    }
                }
                else
                {
                    if (prevDiff.y == 0)
                    {
                        if (prevDiff.x < 0)
                        {
                            rotation = nextDiff.y < 0 ? 180 : 270;
                        }
                        else
                        {
                            rotation = nextDiff.y < 0 ? 90 : 0;
                        }
                    }
                    else
                    {
                        if (prevDiff.y < 0)
                        {
                            rotation = nextDiff.x < 0 ? 0 : 270;
                        }
                        else
                        {
                            rotation = nextDiff.x < 0 ? 90 : 180;
                        }
                    }
                }

                middleSprite->setRotation(rotation);
                target.draw(*middleSprite);
            }

            {
                auto end = _positions.rbegin();
                auto headPos = *end;
                end++;
                auto prevPos = *end;
                auto diff = headPos - prevPos;
                auto headSprite = engine->snakeTiles().getSprite(3);

                auto pos = (sf::Vector2f(headPos) * combinedScale) + (halfSize * scale);
                headSprite->setOrigin(halfSize);
                headSprite->setPosition(pos);

                if (diff.y == 0)
                {
                    headSprite->setRotation(diff.x < 0 ? 180 : 0);
                }
                else
                {
                    headSprite->setRotation(diff.y < 0 ? 270 : 90);
                }
                target.draw(*headSprite);
            }
        }

    }
}