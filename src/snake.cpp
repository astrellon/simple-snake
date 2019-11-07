#include "snake.hpp"

#include <algorithm>
#include <iostream>

#include "engine.hpp"
#include "map.hpp"
#include "keyboard.hpp"

namespace town
{
    SnakePosition::SnakePosition(sf::Vector2i pos, sf::Vector2i diff) :
        _pos(pos), _diff(diff), _tileIndex(0), _rotation(0.0f), _inPortal(false)
    {

    }
    SnakePosition::SnakePosition(sf::Vector2i pos, sf::Vector2i diff, int tileIndex, float rotation, bool inPortal) :
        _pos(pos), _diff(diff), _tileIndex(tileIndex), _rotation(rotation), _inPortal(inPortal)
    {

    }

    SnakePosition::~SnakePosition()
    {

    }

    Snake::Snake() : _length(3), _altSpriteIndex(false)
    {
        _positions.push_back(SnakePosition(sf::Vector2i(0, 0), sf::Vector2i(0, 0)));
    }

    Snake::~Snake()
    {

    }

    bool Snake::willHitSnake(sf::Vector2i position) const
    {
        for (const auto &pos : _positions)
        {
            if (pos.pos() == position)
            {
                return true;
            }
        }

        return false;
    }

    sf::Vector2i Snake::headPosition() const
    {
        return (*_positions.rbegin()).pos();
    }

    sf::Vector2i Snake::neckPosition() const
    {
        return (*(_positions.rbegin() + 1)).pos();
    }

    sf::Vector2i Snake::anklePosition() const
    {
        return (*(_positions.begin() + 1)).pos();
    }

    sf::Vector2i Snake::tailPosition() const
    {
        return (*_positions.begin()).pos();
    }

    SnakePosition &Snake::headData()
    {
        return (*_positions.rbegin());
    }

    SnakePosition &Snake::neckData()
    {
        return (*(_positions.rbegin() + 1));
    }

    SnakePosition &Snake::ankleData()
    {
        return (*(_positions.begin() + 1));
    }

    SnakePosition &Snake::tailData()
    {
        return (*_positions.begin());
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
            auto newPosition = headPosition() + move;
            if (willHitSnake(newPosition))
            {
                if (_positions.size() > 1 && newPosition == neckPosition())
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
                    auto diff = newPosition - headPosition();
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

                    addNewPosition(newPosition, diff);
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

        auto altSpriteIndex = _altSpriteIndex;

        if (_positions.size() == 1)
        {
            drawSprite(engine, target, _positions[0].pos(), 0, 0 + indexOffset(altSpriteIndex));
            altSpriteIndex = !altSpriteIndex;
        }
        else
        {
            for (const auto &pos : _positions)
            {
                drawSprite(engine, target, pos.pos(), pos.rotation(), pos.tileIndex());
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

    void Snake::addNewPosition(sf::Vector2i newPosition, sf::Vector2i diff)
    {
        _positions.push_back(SnakePosition(newPosition, diff));
        if (_positions.size() > _length)
        {
            _positions.erase(_positions.begin());
        }

        {
            auto &tailPos = tailData();
            auto diff = ankleData().diff();
            auto rotation = 0.0f;

            if (diff.y == 0)
            {
                rotation = diff.x < 0 ? 180.0f : 0.0f;
            }
            else
            {
                rotation = diff.y < 0 ? 270.0f : 90.0f;
            }

            tailPos.rotation(rotation);
            tailPos.tileIndex(1 + indexOffset(_altSpriteIndex));
            _altSpriteIndex = !_altSpriteIndex;
        }

        for (auto i = 1; i < _positions.size() - 1; i++)
        {
            const auto &prevPos = _positions[i - 1];
            auto &pos = _positions[i];
            const auto &nextPos = _positions[i + 1];

            auto prevDiff = pos.diff();
            auto nextDiff = nextPos.diff();
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

            pos.rotation(rotation);
            pos.tileIndex(index + indexOffset(_altSpriteIndex));
            _altSpriteIndex = !_altSpriteIndex;
        }

        {
            auto &headPos = headData();
            const auto &prevPos = neckData();
            auto diff = headData().diff();
            auto rotation = 0.0f;

            if (diff.y == 0)
            {
                rotation = diff.x < 0 ? 180.0f : 0.0f;
            }
            else
            {
                rotation = diff.y < 0 ? 270.0f : 90.0f;
            }

            headPos.rotation(rotation);
            headPos.tileIndex(3 + indexOffset(_altSpriteIndex));
            _altSpriteIndex = !_altSpriteIndex;
        }
    }

    int Snake::indexOffset(bool alt)
    {
        return alt ? 4 : 0;
    }
}