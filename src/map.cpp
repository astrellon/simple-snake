#include "map.hpp"

#include <SFML/Graphics.hpp>

#include "engine.hpp"
#include "game_session.hpp"
#include "snake.hpp"

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

    bool Map::hitApple(sf::Vector2i position)
    {
        for (auto iter = _apples.begin(); iter != _apples.end(); ++iter)
        {
            if (iter->position() == position)
            {
                _apples.erase(iter);
                return true;
            }
        }

        return false;
    }

    void Map::update(Engine *engine, sf::Time dt)
    {
        auto &player = engine->currentSession()->player();
        if (player.length() >= 5)
        {

        }
    }

    void Map::draw(Engine *engine, sf::RenderTarget &target)
    {
        auto scale = engine->spriteScale();
        auto combinedScale = engine->spriteScaleCombined();

        auto x = 0, y = 0;
        for (const auto tile : _data)
        {
            auto *sprite = engine->tiles().getSprite(tile);
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
                auto pos = apple.position();
                appleSprite.setPosition(combinedScale * pos.x, combinedScale * pos.y);
                target.draw(appleSprite);
            }
        }
    }
}