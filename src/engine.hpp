#pragma once

#include "non_copyable.hpp"
#include "font_manager.hpp"
#include "texture_manager.hpp"
#include "map_manager.hpp"
#include "tiles.hpp"

namespace town
{
    class Engine : private NonCopyable
    {
        public:
            FontManager &fontManager() const;
            TextureManager &textureManager() const;
            MapManager &mapManager() const;
            Tiles &tiles() const;

            void readDataPaths(const std::string &filename);

        private:
            mutable FontManager _fontManager;
            mutable TextureManager _textureManager;
            mutable MapManager _mapManager;
            mutable Tiles _tiles;
    };
} // town