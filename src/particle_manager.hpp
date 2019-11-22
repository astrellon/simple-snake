#pragma once

#include <vector>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "non_copyable.hpp"
#include "particle_system.hpp"

namespace town
{
    class Tiles;
    class Engine;

    class ParticleManager : private NonCopyable
    {
        public:

            typedef std::vector<std::unique_ptr<ParticleSystem>> ParticlesList;

            ParticleSystem *createSystem(std::size_t numParticles, Tiles *tiles);

            void update(sf::Time dt);
            void draw(Engine *engine, sf::RenderTarget &target);

        private:
            ParticlesList _particles;

            void removeUnusedSystems();
    };
} // town