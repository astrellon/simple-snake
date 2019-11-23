#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <map>

#include "non_copyable.hpp"

namespace town
{
    class Tiles;
    class Engine;

    class TilesManager : private NonCopyable
    {
        public:
            TilesManager(Engine *engine);

            typedef std::map<std::string, std::unique_ptr<Tiles>> TilesMap;

            Tiles *create(const std::string &name, const std::string &textureName, uint spriteSize = 0);

            const Tiles *tiles(const std::string &name) const;
            const TilesMap &tilesMap() const;

        private:

            TilesMap _tilesMap;
            Engine *_engine;
    };
}

