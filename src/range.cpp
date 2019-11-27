#include "range.hpp"

#include <math.h>

#include "utils.hpp"

namespace town
{
    Range::Range(RangeType rangeType, float min, float max) : min(min), max(max), _rangeType(rangeType)
    {

    }

    float Range::randomValue() const
    {
        return get(Utils::randf());
    }

    float Range::get(float t) const
    {
        auto easeValue = getEaseValue(t);
        auto diff = max - min;
        auto value = easeValue * diff;
        return value + min;
    }

    float Range::getEaseValue(float t) const
    {
        switch (_rangeType)
        {
            default:
            case Linear: return t;
            case EaseInQuad: return t * t;
            case EaseOutQuad: return t * (2 - t);
            case EaseInQuart: return t * t * t * t;
            case EaseOutQuart: return 1-(--t) * t * t * t;
        }
    }
} // namespace town
