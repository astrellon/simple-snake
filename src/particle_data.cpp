#include "particle_data.hpp"

#include <math.h>

namespace town
{
    ParticleData::ParticleData() :
        loops(true),
        lifeTime(Range(Linear, 2.5f, 3.5f)),
        emissionAngles(Range(Linear, 0, M_PI * 2.0)),
        emissionSpeeds(Range(Linear, 40, 70)),
        speedOverLife(Range(EaseOutQuart, 0.0f, 1.0f))
    {

    }
} // namespace town
