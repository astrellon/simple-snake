#pragma once

namespace town
{
    class Range
    {
        public:
            Range(float min, float max);

            float randomValue();
            int randomInt(int min, int max);

            float min;
            float max;

            static Range Linear(float min, float max);
    };

} // town