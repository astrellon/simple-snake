#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "non_copyable.hpp"
#include "vector_comparer.hpp"
#include "apple.hpp"
#include "portal.hpp"

namespace town
{
    class Engine;
    class GameSession;
    class Tiles;

    class Map : private NonCopyable
    {
        public:
            Map(Engine *engine, const std::string &mapName, uint width, uint height);
            ~Map();

            const std::string &mapName() const;

            typedef std::vector<int> MapData;
            typedef std::vector<Apple> AppleList;
            typedef std::vector<std::unique_ptr<Portal>> PortalList;

            const MapData &mapData() const;
            uint width() const;
            uint height() const;

            void tile(int x, int y, int tile);
            int tile(int x, int y) const;

            bool canMoveTo(sf::Vector2i position) const;
            AppleList::iterator willHitApple(sf::Vector2i position);
            bool hitApple(sf::Vector2i position);
            void spawnApple(GameSession *gameSession);

            void addPortal(sf::Vector2i pos1, sf::Vector2i pos2);
            bool willHitPortal(sf::Vector2i pos1, sf::Vector2i *result);

            void initTiles(const Tiles *tiles);

            sf::Vector2f calculateMapPosition(sf::Vector2i gridPosition, bool getCenter) const;

            void update(Engine *engine, sf::Time dt);
            void draw(Engine *engine, sf::RenderTarget &target);

        private:
            const std::string _mapName;
            uint _width;
            uint _height;
            MapData _data;
            AppleList _apples;
            PortalList _portals;
            const Tiles *_tileMap;
            Engine *_engine;

            sf::Time _lastSpawnTime;

            sf::VertexArray _mapVerticies;

            void redrawTile(int x, int y);
            void redrawMap();

    };
} // town