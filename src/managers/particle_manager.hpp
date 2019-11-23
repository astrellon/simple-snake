#pragma once

#include <vector>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../non_copyable.hpp"
#include "../particle_system.hpp"

namespace town
{
    class Tiles;
    class Engine;

    class ParticleManager : private NonCopyable
    {
        public:
            ParticleManager(Engine *engine);

            typedef std::vector<std::unique_ptr<ParticleSystem>> ParticlesList;

            ParticleSystem *createSystem(std::size_t numParticles, const Tiles *tiles);
            ParticleSystem *createSystem(std::size_t numParticles, const std::string &tilesName);

            void update(sf::Time dt);
            void draw(sf::RenderTarget &target);

        private:
            Engine *_engine;
            ParticlesList _particles;

            void removeUnusedSystems();
    };
} // town