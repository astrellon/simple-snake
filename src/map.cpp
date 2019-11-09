#include "map.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

#include "engine.hpp"
#include "game_session.hpp"
#include "snake.hpp"
#include "utils.hpp"

namespace town
{
    Map::Map(Engine *engine, const std::string &mapName, uint width, uint height) :
        _mapName(mapName), _width(width), _height(height), _tileMap(nullptr), _engine(engine)
    {
        _data.resize(width * height);
        for (auto i = 0; i < width * height; i++)
        {
            _data[i] = 0;
        }

        _mapVerticies.setPrimitiveType(sf::Triangles);
    }

    Map::~Map()
    {

    }

    const std::string &Map::mapName() const
    {
        return _mapName;
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
        _portals.emplace_back(std::make_unique<Portal>(pos1, pos2));
    }
    bool Map::willHitPortal(sf::Vector2i pos1, sf::Vector2i *result)
    {
        for (auto &portal : _portals)
        {
            if (portal->pos1() == pos1)
            {
                *result = portal->pos2();
                return true;
            }
            if (portal->pos2() == pos1)
            {
                *result = portal->pos1();
                return true;
            }
        }

        return false;
    }

    void Map::initTiles(Tiles *tiles)
    {
        _tileMap = tiles;

        if (tiles == nullptr)
        {
            return;
        }

        redrawMap();
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

        target.draw(_mapVerticies, _tileMap->texture());

        if (_apples.size() > 0)
        {
            sf::Sprite appleSprite(*engine->textureManager()->texture("apple"));
            appleSprite.setScale(scale, scale);
            for (const auto &apple : _apples)
            {
                auto pos = sf::Vector2f(apple.position());
                appleSprite.setPosition(pos * combinedScale);
                target.draw(appleSprite);
            }
        }

        for (const auto &portal : _portals)
        {
            portal->draw(engine, target);
        }
    }

    void Map::redrawMap()
    {
        _mapVerticies.clear();
        if (_tileMap == nullptr)
        {
            return;
        }

        auto vertexCount = 3 * 2 * _width * _height;
        _mapVerticies.resize(vertexCount);

        auto scale = _engine->spriteScale();
        auto mul = _engine->spriteScaleCombined();
        auto size = _engine->spriteSize();

        auto x = 0, y = 0, v = 0;
        for (const auto tile : _data)
        {
            auto spritePosition = _tileMap->getSpritePosition(tile);

            _mapVerticies[v].position = sf::Vector2f(x * mul, y * mul);
            _mapVerticies[v].texCoords = spritePosition;
            _mapVerticies[v + 1].position = sf::Vector2f((x + 1) * mul, y * mul);
            _mapVerticies[v + 1].texCoords = sf::Vector2f(spritePosition.x + size, spritePosition.y);
            _mapVerticies[v + 2].position = sf::Vector2f(x * mul, (y + 1) * mul);
            _mapVerticies[v + 2].texCoords = sf::Vector2f(spritePosition.x, spritePosition.y + size);



            _mapVerticies[v + 3] = _mapVerticies[v + 1];

            _mapVerticies[v + 4].position = sf::Vector2f((x + 1) * mul, (y + 1) * mul);
            _mapVerticies[v + 4].texCoords = sf::Vector2f(spritePosition.x + size, spritePosition.y + size);

            _mapVerticies[v + 5] = _mapVerticies[v + 2];

            v += 6;
            x++;
            if (x >= _width)
            {
                y++;
                x = 0;
            }
        }
    }
}