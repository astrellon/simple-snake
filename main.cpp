#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "src/engine.hpp"
#include "src/font_manager.hpp"
#include "src/map.hpp"
#include "src/tiles.hpp"
#include "src/snake.hpp"
#include "src/keyboard.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    town::Engine engine;
    engine.spriteScale(4.0f);
    engine.readDataPaths("data/data.csv");

    town::Snake player;

    auto sansFont = engine.fontManager().font("sans");
    auto tileTexture = engine.textureManager().texture("tiles");

    auto &tiles = engine.tiles();
    tiles.init(tileTexture, 16, engine.spriteScale());

    auto &mapManager = engine.mapManager();
    auto &map1 = mapManager.createMap("Map 1", 5, 5);
    map1.tile(1, 1, 1);
    map1.tile(2, 1, 2);
    map1.tile(3, 1, 3);
    map1.tile(4, 1, 4);
    map1.tile(0, 2, 8);
    map1.tile(1, 2, 8);
    map1.tile(2, 2, 8);

    // Create a text
    sf::Text text("hello", *sansFont);
    text.setCharacterSize(72);

    sf::Clock timer;

    while (window.isOpen())
    {
        sf::Event event;
        town::Keyboard::resetKeys();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // catch the resize events
            else if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                town::Keyboard::setKeyDown(event.key.code);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                town::Keyboard::setKeyUp(event.key.code);
            }
        }

        auto deltaTime = timer.getElapsedTime().asSeconds();
        timer.restart();

        map1.update(deltaTime);
        player.update(&map1, deltaTime);

        window.clear();
        map1.draw(&engine, window);
        player.draw(&engine, window);
        window.draw(text);
        window.display();
    }

    return 0;
}
