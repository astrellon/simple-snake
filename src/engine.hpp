#pragma once

#include "non_copyable.hpp"
#include "font_manager.hpp"
#include "map_manager.hpp"

namespace town
{
    class Engine : private NonCopyable
    {
        public:
            FontManager &fontManager() const;
            MapManager &mapManager() const;

        private:
            mutable FontManager _fontManager;
            mutable MapManager _mapManager;
    };
} // town