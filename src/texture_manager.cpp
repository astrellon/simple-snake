#include "texture_manager.hpp"

#include <iostream>

namespace town
{

    bool TextureManager::load_texture(const std::string &name, const std::string &filename)
    {
        if (name.empty())
        {
            return false;
        }

        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(filename))
        {
            return false;
        }

        _textures.emplace(name, std::move(texture));
        return true;
    }

    const TextureManager::TextureMap &TextureManager::textures() const
    {
        return _textures;
    }

    const sf::Texture *TextureManager::texture(const std::string &name) const
    {
        auto find = _textures.find(name);
        if (find == _textures.end())
        {
            return nullptr;
        }

        return find->second.get();
    }
}

