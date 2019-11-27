#pragma once

#include <unistd.h>

namespace town
{
    enum RangeType : unsigned char
    {
        Linear, EaseInQuad, EaseOutQuad, EaseInQuart, EaseOutQuart
    };

    class Range
    {
        public:
            Range(RangeType rangeType, float min, float max);

            float randomValue() const;
            float get(float t) const;
            float getEaseValue(float t) const;

            float min;
            float max;

            inline RangeType rangeType() const
            {
                return _rangeType;
            }

        private:
            RangeType _rangeType;
    };

} // town