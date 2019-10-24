#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "src/engine.hpp"
#include "src/font_manager.hpp"
#include "src/map.hpp"
#include "src/tiles.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    town::Engine engine;
    engine.readDataPaths("data/data.csv");

    auto sansFont = engine.fontManager().font("sans");
    auto tileTexture = engine.textureManager().texture("tiles");

    auto &tiles = engine.tiles();
    tiles.init(tileTexture, 16);

    auto &mapManager = engine.mapManager();
    auto &map1 = mapManager.createMap("Map 1", 5, 5);
    map1.setTile(1, 1, 1);
    map1.setTile(2, 1, 2);
    map1.setTile(3, 1, 3);
    map1.setTile(2, 2, 3);
    map1.setTile(2, 4, 5);

    // Create a text
    sf::Text text("hello", *sansFont);
    text.setCharacterSize(72);

    sf::Clock timer;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // catch the resize events
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        auto deltaTime = timer.getElapsedTime().asSeconds();
        timer.restart();

        map1.update(deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            shape.move(-100.0f * deltaTime, 0.0f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            shape.move(100.0f * deltaTime, 0.0f);
        }

        window.clear();
        map1.draw(&engine, window);
        window.draw(text);
        window.display();
    }

    return 0;
}
