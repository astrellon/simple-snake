#include "range.hpp"

#include <math.h>

#include "utils.hpp"

namespace town
{
    Range::Range(float min, float max) : min(min), max(max)
    {

    }

    int Range::randomInt(int min, int max)
    {
        auto diff = (float)(max - min);
        auto value = randomValue() * diff;
        return round(value) - min;
    }

    float Range::randomValue()
    {
        return Utils::randf(min, max);
    }

    Range Range::Linear(float min, float max)
    {
        return Range(min, max);
    }
} // namespace town
