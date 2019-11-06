#include "snake.hpp"

#include <algorithm>
#include <iostream>

#include "engine.hpp"
#include "map.hpp"
#include "keyboard.hpp"

namespace town
{
    Snake::Snake() : _length(3), _altSpriteIndex(false)
    {
        _positions.push_back(sf::Vector2i(0, 0));
        _positionsDiffs.push_back(sf::Vector2i(0, 0));
    }

    Snake::~Snake()
    {

    }

    bool Snake::willHitSnake(sf::Vector2i position) const
    {
        return std::find(_positions.begin(), _positions.end(), position) != _positions.end();
    }

    sf::Vector2i Snake::headPosition() const
    {
        return *_positions.rbegin();
    }

    std::size_t Snake::length() const
    {
        return _positions.size();
    }
    void Snake::length(std::size_t newLength)
    {
        _length = newLength;
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
            if (willHitSnake(newPosition))
            {
                if (_positions.size() > 1 && newPosition == *(_positions.rbegin() + 1))
                {
                    std::cout << "not a real hit" << std::endl;
                }
                else
                {
                    std::cout << "oh no!" << std::endl;
                }
            }
            else
            {
                if (map->canMoveTo(newPosition))
                {
                    auto diff = newPosition - *(_positions.rbegin());
                    if (map->hitApple(newPosition))
                    {
                        _length++;
                    }
                    else
                    {
                        sf::Vector2i portalPosition;
                        if (map->willHitPortal(newPosition, &portalPosition))
                        {
                            newPosition = portalPosition;
                        }
                    }

                    _positions.push_back(newPosition);
                    _positionsDiffs.push_back(diff);
                    if (_positions.size() > _length)
                    {
                        _positions.erase(_positions.begin());
                        _positionsDiffs.erase(_positionsDiffs.begin());
                    }
                }

                _altSpriteIndex = !_altSpriteIndex;
            }
        }
    }

    void Snake::draw(Engine *engine, sf::RenderTarget &target)
    {
        const float scale = engine->spriteScale();
        const float size = engine->spriteSize();
        const float combinedScale = engine->spriteScaleCombined();
        const sf::Vector2f halfSize(size * 0.5f, size * 0.5f);

        auto altSpriteIndex = _altSpriteIndex;

        if (_positions.size() == 1)
        {
            drawSprite(engine, target, _positions[0], 0, 0 + indexOffset(altSpriteIndex));
            altSpriteIndex = !altSpriteIndex;
        }
        else
        {
            {
                auto tailPos = _positions[0];
                auto diff = _positionsDiffs[1];
                auto rotation = 0.0f;

                if (diff.y == 0)
                {
                    rotation = diff.x < 0 ? 180.0f : 0.0f;
                }
                else
                {
                    rotation = diff.y < 0 ? 270.0f : 90.0f;
                }

                drawSprite(engine, target, tailPos, rotation, 1 + indexOffset(altSpriteIndex));
                altSpriteIndex = !altSpriteIndex;
            }

            for (auto i = 1; i < _positions.size() - 1; i++)
            {
                const auto &prevPos = _positions[i - 1];
                const auto &pos = _positions[i];
                const auto &nextPos = _positions[i + 1];

                auto prevDiff = _positionsDiffs[i];
                auto nextDiff = _positionsDiffs[i + 1];
                auto isBend = prevDiff == nextDiff;
                auto index = isBend ? 2 : 8;

                auto rotation = 0.0f;

                if (isBend)
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

                drawSprite(engine, target, pos, rotation, index + indexOffset(altSpriteIndex));
                altSpriteIndex = !altSpriteIndex;
            }

            {
                auto end = _positions.rbegin();
                auto headPos = *end;
                end++;
                auto prevPos = *end;
                auto diff = *(_positionsDiffs.rbegin());
                auto headSprite = engine->snakeTiles().getSprite(3);
                auto rotation = 0.0f;

                if (diff.y == 0)
                {
                    rotation = diff.x < 0 ? 180.0f : 0.0f;
                }
                else
                {
                    rotation = diff.y < 0 ? 270.0f : 90.0f;
                }

                drawSprite(engine, target, headPos, rotation, 3 + indexOffset(altSpriteIndex));
                altSpriteIndex = !altSpriteIndex;
            }
        }
    }

    void Snake::drawSprite(Engine *engine, sf::RenderTarget &target, sf::Vector2i position, float rotation, int index)
    {
        const float size = engine->spriteSize();
        const float scale = engine->spriteScale();
        const float combinedScale = engine->spriteScaleCombined();

        const sf::Vector2f halfSize(size * 0.5f, size * 0.5f);

        auto sprite = engine->snakeTiles().getSprite(index);
        sprite->setOrigin(halfSize);

        auto pos = (sf::Vector2f(position) * combinedScale) + (halfSize * scale);
        sprite->setPosition(pos);
        sprite->setRotation(rotation);

        target.draw(*sprite);
    }

    int Snake::indexOffset(bool alt)
    {
        return alt ? 4 : 0;
    }
}