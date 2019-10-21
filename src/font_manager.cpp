#include "font_manager.hpp"

#include <iostream>

namespace town
{
    const FontManager::FontMap &FontManager::fonts()
    {
        return _fonts;
    }

    bool FontManager::load_font(const std::string &name, const std::string &filename)
    {
        if (name.empty())
        {
            return false;
        }

        auto font = std::make_unique<sf::Font>();
        if (!font->loadFromFile(filename))
        {
            return false;
        }

        _fonts.emplace(name, std::move(font));
        return true;
    }

    const sf::Font *FontManager::font(const std::string &name)
    {
        auto find = _fonts.find(name);
        if (find == _fonts.end())
        {
            return nullptr;
        }

        return find->second.get();
    }

    // bool FontManager::load_default_fonts()
    // {
    //     if (!load_font("mono", "data/fonts/LiberationMono-Regular.ttf"))
    //     {
    //         std::cout << "Failed to load mono font\n";
    //         return false;
    //     }
    //     if (!load_font("sans", "data/fonts/LiberationSans-Regular.ttf"))
    //     {
    //         std::cout << "Failed to load sans font\n";
    //         return false;
    //     }
    //     return true;
    // }
}

