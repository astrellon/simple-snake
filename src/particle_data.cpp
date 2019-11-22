#include "particle_data.hpp"

#include <math.h>

namespace town
{
    ParticleData::ParticleData() :
        loops(true),
        lifeTime(sf::seconds(3.0f)),
        _emissionAngles(std::make_shared<LinearRange>(0, M_PI * 2.0)),
        _emissionSpeeds(std::make_shared<LinearRange>(40, 70))
    {

    }

    Range *ParticleData::emissionAngles()
    {
        return _emissionAngles.get();
    }
    void ParticleData::emissionAngles(Range *range)
    {
        _emissionAngles.reset(range);
    }

    Range *ParticleData::emissionSpeeds()
    {
        return _emissionSpeeds.get();
    }
    void ParticleData::emissionSpeeds(Range *range)
    {
        _emissionSpeeds.reset(range);
    }
} // namespace town
