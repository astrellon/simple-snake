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
            sf::Time lifeTime;

            Range emissionAngles;
            Range emissionSpeeds;
    };
} // town