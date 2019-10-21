#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "src/engine.hpp"
#include "src/map.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    town::Engine engine;

    auto &fontManager = engine.fontManager();
    fontManager.load_font("sans", "data/NotoSans-Regular.ttf");

    auto sansFont = fontManager.font("sans");

    auto &mapManager = engine.mapManager();
    auto &map1 = mapManager.create_map("Map 1");

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
        window.draw(shape);
        window.draw(text);
        map1.draw(window);
        window.display();
    }

    return 0;
}
