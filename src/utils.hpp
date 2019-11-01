#pragma once

#include <functional>
#include <string>
#include <vector>
#include <random>

namespace town
{
    class Utils
    {
        public:
            static std::vector<std::string> split(const std::string &input, char delimiter, bool trimTokens);

            static std::string &rtrim(std::string & str);
            static std::string &ltrim(std::string & str);
            static std::string &trim(std::string & str);

            typedef std::function<bool (const std::string &)> LineReader;
            static void readCSVLines(const std::string &filename, LineReader lineReader);

            static inline float randf(float min = 0.0f, float max = 1.0f)
            {
                std::uniform_real_distribution<float> dist(min, max);
                return dist(_rand);
            }
            static inline int randi(int min = 0, int max = 1)
            {
                auto floatValue = randf(static_cast<float>(min), static_cast<float>(max));

                return static_cast<int>(floatValue);
            }

        private:
            Utils();

            static std::random_device _rd;
            static std::mt19937 _rand;

            public:
    };
} // town