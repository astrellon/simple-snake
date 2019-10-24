#pragma once

#include <string>
#include <vector>

namespace town
{
    class Utils
    {
        public:
            static std::vector<std::string> split(const std::string &input, char delimiter, bool trimTokens);

            static std::string &rtrim(std::string & str);
            static std::string &ltrim(std::string & str);
            static std::string &trim(std::string & str);

        private:
            Utils();
    };
} // town