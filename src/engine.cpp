#include "engine.hpp"

#include <iostream>
#include <fstream>

#include "utils.hpp"

namespace town
{
    FontManager &Engine::fontManager() const
    {
        return _fontManager;
    }

    TextureManager &Engine::textureManager() const
    {
        return _textureManager;
    }

    MapManager &Engine::mapManager() const
    {
        return _mapManager;
    }

    Tiles &Engine::tiles() const
    {
        return _tiles;
    }

    void Engine::readDataPaths(const std::string &filename)
    {
        std::ifstream data(filename);

        std::string line;
        while (std::getline(data, line))
        {
            if (line.size() == 0 || line[0] == '#')
            {
                continue;
            }

            auto tokens = Utils::split(line, ',', true);
            if (tokens[0] == "font")
            {
                _fontManager.load_font(tokens[1], "data/" + tokens[2]);
            }
            else if (tokens[0] == "texture")
            {
                _textureManager.load_texture(tokens[1], "data/" + tokens[2]);
            }
            else
            {
                std::cout << "Unknown data path line: " << line << std::endl;
            }
        }
    }
}