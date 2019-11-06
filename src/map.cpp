#include "map.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

#include "engine.hpp"
#include "game_session.hpp"
#include "snake.hpp"
#include "utils.hpp"

namespace town
{
    Map::Map(const std::string &mapName, uint width, uint height) :
        _mapName(mapName), _width(width), _height(height)
    {
        _data.resize(width * height);
        for (auto i = 0; i < width * height; i++)
        {
            _data[i] = 0;
        }
    }

    Map::~Map()
    {

    }

    const std::string &Map::mapName() const
    {
        return _mapName;
    }

    Map::MapData &Map::mapData()
    {
        return _data;
    }

    const Map::MapData &Map::mapData() const
    {
        return _data;
    }

    uint Map::width() const
    {
        return _width;
    }

    uint Map::height() const
    {
        return _height;
    }

    void Map::tile(int x, int y, int tile)
    {
        auto index = y * _width + x;
        if (index >= 0 && index < _data.size())
        {
            _data[index] = tile;
        }
    }

    int Map::tile(int x, int y) const
    {
        auto index = y * _width + x;
        if (index >= 0 && index < _data.size())
        {
            return _data[index];
        }

        return -1;
    }

    bool Map::canMoveTo(sf::Vector2i position) const
    {
        if (position.x < 0 || position.x >= _width ||
            position.y < 0 || position.y >= _height)
        {
            return false;
        }

        auto tileData = tile(position.x, position.y);
        return tileData < 8;
    }

    Map::AppleList::iterator Map::willHitApple(sf::Vector2i position)
    {
        for (auto iter = _apples.begin(); iter != _apples.end(); ++iter)
        {
            if (iter->position() == position)
            {
                return iter;
            }
        }

        return _apples.end();
    }

    bool Map::hitApple(sf::Vector2i position)
    {
        auto apple = willHitApple(position);
        if (apple != _apples.end())
        {
            _apples.erase(apple);
            return true;
        }

        return false;
    }

    void Map::spawnApple(GameSession *gameSession)
    {
        auto counter = 10;
        while(counter--)
        {
            auto posX = Utils::randi(0, _width);
            auto posY = Utils::randi(0, _height);
            sf::Vector2i pos(posX, posY);
            if (canMoveTo(pos) && willHitApple(pos) == _apples.end())
            {
                if (gameSession != nullptr && gameSession->player().willHitSnake(pos))
                {
                    continue;
                }

                _apples.push_back(Apple(pos));
                return;
            }
        }

        std::cout << "Unable to find a place to put apple" << std::endl;
    }

    void Map::addPortal(sf::Vector2i pos1, sf::Vector2i pos2)
    {
        _portals.emplace_back(pos1, pos2);
    }
    bool Map::willHitPortal(sf::Vector2i pos1, sf::Vector2i *result)
    {
        for (auto &iter : _portals)
        {
            if (iter.first == pos1)
            {
                *result = iter.second;
                return true;
            }
            if (iter.second == pos1)
            {
                *result = iter.first;
                return true;
            }
        }

        return false;
    }

    void Map::update(Engine *engine, sf::Time dt)
    {
        auto &player = engine->currentSession()->player();
        auto time = engine->timeSinceStart() - _lastSpawnTime;
        if (time.asSeconds() > 4.0f)
        {
            _lastSpawnTime = engine->timeSinceStart();
            if (_apples.size() < 10)
            {
                spawnApple(engine->currentSession());
            }
        }
    }

    void Map::draw(Engine *engine, sf::RenderTarget &target)
    {
        auto scale = engine->spriteScale();
        auto combinedScale = engine->spriteScaleCombined();

        auto x = 0, y = 0;
        for (const auto tile : _data)
        {
            auto *sprite = engine->mapTiles().getSprite(tile);
            if (sprite == nullptr)
            {
                continue;
            }

            sprite->setPosition(combinedScale * x, combinedScale * y);
            target.draw(*sprite);

            x++;
            if (x >= _width)
            {
                y++;
                x = 0;
            }
        }

        if (_apples.size() > 0)
        {
            sf::Sprite appleSprite(*engine->textureManager().texture("apple"));
            appleSprite.setScale(scale, scale);
            for (const auto &apple : _apples)
            {
                auto pos = sf::Vector2f(apple.position());
                appleSprite.setPosition(pos * combinedScale);
                target.draw(appleSprite);
            }
        }

        if (_portals.size() > 0)
        {
            auto sprite = engine->portalTiles().getSprite(0);

            for (const auto &portalPair : _portals)
            {
                auto pos1 = sf::Vector2f(portalPair.first);
                sprite->setPosition(pos1 * combinedScale);
                target.draw(*sprite);

                auto pos2 = sf::Vector2f(portalPair.second);
                sprite->setPosition(pos2 * combinedScale);
                target.draw(*sprite);
            }
        }
    }
}