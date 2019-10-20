#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "src/font_manager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    town::FontManager fontManager;
    fontManager.load_font("sans", "data/NotoSans-Regular.ttf");

    auto sans_font = fontManager.font("sans");

    // Create a text
    sf::Text text("hello", *sans_font);
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
        window.display();
    }

    return 0;
}
