#include "particle_data.hpp"

#include <math.h>

namespace town
{
    ParticleData::ParticleData() :
        loops(true),
        lifeTime(sf::seconds(3.0f)),
        emissionAngles(Range(0, M_PI * 2.0)),
        emissionSpeeds(Range(40, 70))
    {

    }
} // namespace town
