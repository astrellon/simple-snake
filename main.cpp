#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include "src/engine.hpp"
#include "src/managers/font_manager.hpp"
#include "src/map.hpp"
#include "src/tiles.hpp"
#include "src/snake.hpp"
#include "src/game_session.hpp"
#include "src/particle_system.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Snake");
    window.setVerticalSyncEnabled(true);

    town::Engine engine(window);
    engine.spriteScale(4.0f);
    engine.readDataPaths("data/data.csv");

    auto textureManager = engine.textureManager();

    auto sansFont = engine.fontManager()->font("sans");

    auto spriteSize = static_cast<uint>(engine.spriteSize());
    auto spriteScale = engine.spriteScale();

    auto mapTiles = engine.tilesManager()->tiles("map");
    auto portalTiles = engine.tilesManager()->tiles("portal");

    auto portalSprite1 = portalTiles->getSprite(0);

    auto mapManager = engine.mapManager();
    auto map1 = mapManager->loadMap("data/testMap.csv");
    if (map1 == nullptr)
    {
        std::cout << "Cannot play without a map!" << std::endl;
        return 1;
    }
    map1->initTiles(mapTiles);

    auto gameSession = engine.startGameSession();
    gameSession->currentMap(map1);

    // Create a text
    // sf::Text text("hello", *sansFont);
    // text.setCharacterSize(72);

    while (window.isOpen())
    {
        engine.processEvents();

        engine.preUpdate();
        engine.update();
        engine.draw();
    }

    return 0;
}
