#include "engine.hpp"

namespace town
{
    FontManager &Engine::fontManager() const
    {
        return _fontManager;
    }

    MapManager &Engine::mapManager() const
    {
        return _mapManager;
    }
}