#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "particle_data.hpp"

namespace town
{
    class Engine;
    class Tiles;

    class ParticleSystem
    {
        public:
            typedef std::vector<sf::Vector2f> Vectors;
            typedef std::vector<float> Times;
            typedef std::vector<bool> Booleans;

            ParticleSystem(std::size_t numParticles, const Tiles *tiles);

            void initParticles();

            std::size_t numParticles() const;
            const Tiles *tiles() const;
            bool hasEnded() const;

            ParticleData &data();
            const ParticleData &data() const;
            void data(const ParticleData &data);

            void restart();

            void update(sf::Time dt);
            void draw(Engine *engine, sf::RenderTarget &target);

        private:
            Vectors _positions;
            Vectors _velocity;
            Times _lifeLeft;

            ParticleData _data;

            bool _hasEnded;

            const Tiles *_tiles;
            sf::VertexArray _vertexArray;

            void restart(std::size_t index);
    };

} // town

