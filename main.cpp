#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <thread>
#include <chrono>

#include "src/engine.hpp"
#include "src/font_manager.hpp"
#include "src/map.hpp"
#include "src/tiles.hpp"
#include "src/snake.hpp"
#include "src/game_session.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Snake");

    town::Engine engine(window);
    engine.spriteScale(4.0f);
    engine.readDataPaths("data/data.csv");

    auto sansFont = engine.fontManager().font("sans");
    auto tileTexture = engine.textureManager().texture("mapTiles");
    auto snakeTexture = engine.textureManager().texture("snakeTiles");

    auto &mapTiles = engine.mapTiles();
    mapTiles.init(tileTexture, static_cast<uint>(engine.spriteSize()), engine.spriteScale());

    auto &snakeTiles = engine.snakeTiles();
    snakeTiles.init(snakeTexture, static_cast<uint>(engine.spriteSize()), engine.spriteScale());

    auto &mapManager = engine.mapManager();
    auto map1 = mapManager.loadMap("data/testMap.csv");
    if (map1 == nullptr)
    {
        std::cout << "Cannot play without a map!" << std::endl;
        return 1;
    }

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
