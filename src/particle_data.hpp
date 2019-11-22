#pragma once

#include <memory>

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

            Range *emissionAngles();
            void emissionAngles(Range *range);

            Range *emissionSpeeds();
            void emissionSpeeds(Range *range);

        private:
            std::shared_ptr<Range> _emissionAngles;
            std::shared_ptr<Range> _emissionSpeeds;
    };
} // town