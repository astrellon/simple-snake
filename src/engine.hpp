#pragma once

#include "non_copyable.hpp"
#include "font_manager.hpp"
#include "map_manager.hpp"
#include "tiles.hpp"

namespace town
{
    class Engine : private NonCopyable
    {
        public:
            FontManager &fontManager() const;
            MapManager &mapManager() const;
            Tiles &tiles() const;

        private:
            mutable FontManager _fontManager;
            mutable MapManager _mapManager;
            mutable Tiles _tiles;
    };
} // town