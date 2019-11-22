#pragma once

#include <SFML/System.hpp>

#include "range.hpp"

namespace town
{
    struct ParticleData
    {
        public:
            ParticleData();

            bool loops;

            Range emissionAngles;
            Range emissionSpeeds;
            Range lifeTime;
    };
} // town