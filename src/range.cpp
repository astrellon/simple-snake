#include "range.hpp"

#include <math.h>

#include "utils.hpp"

namespace town
{
    int Range::randomInt(int min, int max)
    {
        auto diff = (float)(max - min);
        auto value = randomValue() * diff;
        return round(value) - min;
    }

    LinearRange::LinearRange(float min, float max) : _min(min), _max(max)
    {

    }

    float LinearRange::randomValue()
    {
        return Utils::randf(_min, _max);
    }
} // namespace town
