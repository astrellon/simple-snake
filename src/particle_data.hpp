#pragma once

#include <SFML/System.hpp>

namespace town
{
    struct ParticleData
    {
        ParticleData();

        bool loops;
        sf::Time lifeTime;
    };
} // town