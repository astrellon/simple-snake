#include "particle_system.hpp"

#include <iostream>

#include "engine.hpp"
#include "utils.hpp"

namespace town
{
    ParticleSystem::ParticleSystem(std::size_t numParticles, Tiles *tiles) : _tiles(tiles), _hasEnded(false)
    {
        _positions.resize(numParticles);
        _velocity.resize(numParticles);
        _lifeLeft.resize(numParticles);

        _vertexArray.resize(numParticles * 6);
        _vertexArray.setPrimitiveType(sf::Triangles);
    }

    void ParticleSystem::initParticles()
    {
        auto num = numParticles();
        for (auto i = 0; i < num; i++)
        {
            restart(i);
        }
    }

    std::size_t ParticleSystem::numParticles() const
    {
        return _positions.size();
    }

    bool ParticleSystem::hasEnded() const
    {
        return _hasEnded;
    }

    ParticleData &ParticleSystem::data()
    {
        return _data;
    }
    const ParticleData &ParticleSystem::data() const
    {
        return _data;
    }
    void ParticleSystem::data(const ParticleData &data)
    {
        _data = data;
    }

    void ParticleSystem::update(sf::Time dt)
    {
        if (_hasEnded)
        {
            return;
        }

        auto num = numParticles();

        auto dtSeconds = dt.asSeconds();
        for (auto i = 0; i < num; i++)
        {
            _lifeLeft[i] -= dtSeconds;
            if (_lifeLeft[i] <= 0.0f && _data.loops)
            {
                restart(i);
            }
        }

        auto screenSpriteSize = _tiles->combinedSpriteSize();
        auto half = screenSpriteSize * 0.5f;
        sf::Vector2f topLeft(-half, -half);
        sf::Vector2f topRight(half, -half);
        sf::Vector2f bottomLeft(-half, half);
        sf::Vector2f bottomRight(half, half);

        auto spriteSize = _tiles->spriteSize();
        sf::Vector2f texTopRight(spriteSize, 0);
        sf::Vector2f texBottomLeft(0, spriteSize);
        sf::Vector2f texBottomRight(spriteSize, spriteSize);
        auto seconds = dt.asSeconds();

        auto hasAlive = false;

        for (auto i = 0, vi = 0; i < num; i++, vi += 6)
        {
            auto pos = (_positions[i] += _velocity[i] * seconds);
            if (!_data.loops)
            {
                auto age = _lifeLeft[i];
                if (age <= 0.0f)
                {
                    for (auto j = 0; j < 6; j++)
                    {
                        _vertexArray[vi + j].position = sf::Vector2f(0, 0);
                        _vertexArray[vi + j].texCoords = sf::Vector2f(0, 0);
                    }

                    continue;
                }
                else
                {
                    hasAlive = true;
                }
            }

            auto texPos = sf::Vector2f(0, 0);
            _vertexArray[vi    ].position = pos + topLeft;
            _vertexArray[vi    ].texCoords = texPos;
            _vertexArray[vi + 1].position = pos + topRight;
            _vertexArray[vi + 1].texCoords = texPos + texTopRight;
            _vertexArray[vi + 2].position = pos + bottomLeft;
            _vertexArray[vi + 2].texCoords = texPos + texBottomLeft;

            _vertexArray[vi + 3].position = pos + topRight;
            _vertexArray[vi + 3].texCoords = texPos + texTopRight;
            _vertexArray[vi + 4].position = pos + bottomRight;
            _vertexArray[vi + 4].texCoords = texPos + texBottomRight;
            _vertexArray[vi + 5].position = pos + bottomLeft;
            _vertexArray[vi + 5].texCoords = texPos + texBottomLeft;
        }

        _hasEnded = !hasAlive;
    }

    void ParticleSystem::draw(Engine *engine, sf::RenderTarget &target)
    {
        if (_hasEnded)
        {
            return;
        }

        target.draw(_vertexArray, _tiles->texture());
    }

    void ParticleSystem::restart(std::size_t index)
    {
        _positions[index] = sf::Vector2f(50, 50);

        auto angle = _data.emissionAngles.randomValue();
        auto speed = _data.emissionSpeeds.randomValue();
        auto dx = cos(angle) * speed;
        auto dy = sin(angle) * speed;
        _velocity[index] = sf::Vector2f(dx, dy);
        _lifeLeft[index] = _data.lifeTime.randomValue();
    }
} // namespace town
