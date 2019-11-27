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
            typedef std::vector<std::size_t> TileIndicies;

            ParticleSystem(std::size_t numParticles, const Tiles *tiles);

            void initParticles();

            std::size_t numParticles() const;
            const Tiles *tiles() const;
            bool hasEnded() const;

            sf::Vector2f &emissionPosition();
            const sf::Vector2f &emissionPosition() const;
            void emissionPosition(const sf::Vector2f &position);

            ParticleData &data();
            const ParticleData &data() const;
            void data(const ParticleData &data);

            void restart();

            void update(sf::Time dt);
            void draw(Engine *engine, sf::RenderTarget &target);

        private:
            sf::Vector2f _emissionPosition;
            Vectors _positions;
            Vectors _velocity;
            TileIndicies _tileIndicies;
            Times _lifeLeft;
            Times _startingLife;

            ParticleData _data;

            bool _hasEnded;

            const Tiles *_tiles;
            sf::VertexArray _vertexArray;

            void restart(std::size_t index);
    };

} // town

