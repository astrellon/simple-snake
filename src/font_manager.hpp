#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <map>

namespace town
{
    class FontManager
    {
        public:
            FontManager();
            ~FontManager();

            typedef std::map<std::string, std::unique_ptr<sf::Font>> FontMap;
            const FontMap &fonts();

            bool load_font(const std::string &name, const std::string &filename);
            const sf::Font *font(const std::string &name);

        private:

            FontMap _fonts;
    };
}

