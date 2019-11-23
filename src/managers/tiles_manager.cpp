#include "tiles_manager.hpp"

#include <iostream>

#include "../engine.hpp"

namespace town
{
    TilesManager::TilesManager(Engine *engine) :
        _engine(engine)
    {

    }

    Tiles *TilesManager::create(const std::string &name, const std::string &textureName, uint spriteSize)
    {
        auto texture = _engine->textureManager()->texture(textureName);
        if (texture == nullptr)
        {
            std::cout << "Unable to find " << textureName << " for tiles " << name << std::endl;
            return nullptr;
        }

        auto spriteScale = _engine->spriteScale();

        auto result = std::make_unique<Tiles>();
        if (spriteSize == 0)
        {
            spriteSize = static_cast<uint>(_engine->spriteSize());
        }
        result->init(texture, spriteSize, spriteScale);

        auto resultPtr = result.get();
        _tilesMap.emplace(name, std::move(result));
        return resultPtr;
    }

    const TilesManager::TilesMap &TilesManager::tilesMap() const
    {
        return _tilesMap;
    }

    const Tiles *TilesManager::tiles(const std::string &name) const
    {
        auto find = _tilesMap.find(name);
        if (find == _tilesMap.end())
        {
            std::cout << "Unable to find tiles: " << name << std::endl;
            return nullptr;
        }

        return find->second.get();
    }
}

