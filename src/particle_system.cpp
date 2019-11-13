#include "particle_system.hpp"

#include <iostream>

#include "engine.hpp"
#include "utils.hpp"

namespace town
{
    ParticleSystem::ParticleSystem(std::size_t numParticles, Tiles *tiles) : _tiles(tiles)
    {
        _positions.resize(numParticles);
        _velocity.resize(numParticles);
        _ages.resize(numParticles);

        _vertexArray.resize(numParticles * 6);
        _vertexArray.setPrimitiveType(sf::Triangles);

        for (auto i = 0; i < numParticles; i++)
        {
            restart(i);
        }
    }

    std::size_t ParticleSystem::numParticles() const
    {
        return _positions.size();
    }

    void ParticleSystem::update(sf::Time dt)
    {
        auto maxTime = sf::seconds(3.0f);
        auto num = numParticles();

        for (auto i = 0; i < num; i++)
        {
            _ages[i] += dt;
            if (_ages[i] > maxTime)
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

        for (auto i = 0, vi = 0; i < num; i++, vi += 6)
        {
            auto pos = (_positions[i] += _velocity[i] * seconds);
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
    }

    void ParticleSystem::draw(Engine *engine, sf::RenderTarget &target)
    {
        target.draw(_vertexArray, _tiles->texture());
    }

    void ParticleSystem::restart(std::size_t index)
    {
        _positions[index] = sf::Vector2f(50, 50);

        auto dx = Utils::randf(-50.0f, 50.0f);
        auto dy = Utils::randf(-50.0f, 50.0f);
        _velocity[index] = sf::Vector2f(dx, dy);
        _ages[index] = sf::microseconds(0);
    }
} // namespace town
