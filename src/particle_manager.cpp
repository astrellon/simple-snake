#include "particle_manager.hpp"

#include <iostream>

#include "particle_system.hpp"
#include "engine.hpp"

namespace town
{
    ParticleManager::ParticleManager(Engine *engine) : _engine(engine)
    {

    }

    ParticleSystem *ParticleManager::createSystem(std::size_t numParticles, const Tiles *tiles)
    {
        for (const auto &iter : _particles)
        {
            if (!iter->hasEnded())
            {
                continue;
            }

            if (iter->numParticles() == numParticles && iter->tiles() == tiles)
            {
                iter->initParticles();
                return iter.get();
            }
        }
        auto result = std::make_unique<ParticleSystem>(numParticles, tiles);
        auto ptrResult = result.get();
        _particles.emplace_back(std::move(result));
        return ptrResult;
    }
    ParticleSystem *ParticleManager::createSystem(std::size_t numParticles, const std::string &tilesName)
    {
        auto tiles = _engine->tilesManager()->tiles(tilesName);
        return createSystem(numParticles, tiles);
    }

    void ParticleManager::update(sf::Time dt)
    {
        for (auto &iter : _particles)
        {
            iter->update(dt);
        }
    }

    void ParticleManager::draw(sf::RenderTarget &target)
    {
        for (auto &iter : _particles)
        {
            iter->draw(_engine, target);
        }
    }

    void ParticleManager::removeUnusedSystems()
    {
        for (auto i = 0; i < _particles.size(); i++)
        {
            if (_particles[i]->hasEnded())
            {
                _particles.erase(_particles.begin() + i);
                i--;
            }
        }
    }
} // namespace town
