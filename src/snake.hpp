#pragma once

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace town
{
    class Engine;
    class Map;

    class SnakePosition
    {
        public:
            SnakePosition(sf::Vector2i pos, sf::Vector2i diff, int tileIndex, float rotation, bool inPortal);
            ~SnakePosition();

            inline sf::Vector2i pos() const { return _pos; }
            inline sf::Vector2i diff() const { return _diff; }

            inline int tileIndex() const { return _tileIndex; }
            inline void tileIndex(int index) { _tileIndex = index; }

            inline float rotation() const { return _rotation; }
            inline void rotation(float rotation) { _rotation  =rotation; }

            inline bool inPortal() const { return _inPortal; }
            inline void inPortal(bool inPortal) { _inPortal = inPortal; }

            static SnakePosition Empty();
            static SnakePosition Basic(sf::Vector2i pos, sf::Vector2i diff, bool inPortal);

        private:
            sf::Vector2i _pos;
            sf::Vector2i _diff;
            int _tileIndex;
            float _rotation;
            bool _inPortal;
    };

    class Snake
    {
        public:
            Snake();
            ~Snake();

            void update(Map *map, sf::Time dt);
            void draw(Engine *engine, sf::RenderTarget &target);

            typedef std::vector<SnakePosition> PositionList;

            bool willHitSnake(sf::Vector2i position) const;
            sf::Vector2i headPosition() const;
            sf::Vector2i neckPosition() const;
            sf::Vector2i anklePosition() const;
            sf::Vector2i tailPosition() const;

            SnakePosition &headData();
            SnakePosition &neckData();
            SnakePosition &ankleData();
            SnakePosition &tailData();

            std::size_t length() const;
            void length(std::size_t newLength);

            std::size_t currentLength() const;

        private:
            PositionList _positions;
            int _length;
            int _currentLength;
            bool _keyPressed;
            bool _altSpriteIndex;

            void drawSprite(Engine *engine, sf::RenderTarget &target, sf::Vector2i position, float rotation, int index);

            void addNewPosition(sf::Vector2i newPosition, sf::Vector2i diff, bool inPortal);

            static int indexOffset(bool alt);
    };
} // town