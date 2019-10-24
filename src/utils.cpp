#include "utils.hpp"

#include <sstream>
#include <algorithm>

namespace town
{
    std::vector<std::string> Utils::split(const std::string &input, char delimiter, bool trimTokens)
    {
        std::vector<std::string> result;

        std::stringstream sstream(input);
        std::string token;
        while (std::getline(sstream, token, ','))
        {
            if (trimTokens)
            {
                trim(token);
            }
            result.push_back(token);
        }

        return result;
    }

    std::string &Utils::ltrim(std::string & str)
    {
        auto it2 = std::find_if(str.begin(), str.end(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
        str.erase(str.begin(), it2);
        return str;
    }

    std::string &Utils::rtrim(std::string & str)
    {
        auto it1 = std::find_if(str.rbegin(), str.rend(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
        str.erase(it1.base(), str.end());
        return str;
    }

    std::string &Utils::trim(std::string & str)
    {
        return ltrim(rtrim(str));
    }
}