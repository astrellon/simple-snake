#pragma once

namespace town
{
    class Range
    {
        public:
            virtual float randomValue() = 0;
            int randomInt(int min, int max);
    };

    class LinearRange : public Range
    {
        public:
            LinearRange(float min, float max);

            virtual float randomValue();

        private:
            float _min;
            float _max;
    };
} // town