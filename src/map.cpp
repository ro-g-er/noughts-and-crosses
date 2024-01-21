#include "map.h"
#include <iostream>
#include <SFML/Graphics.hpp>


void Map::map() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(600, 600), "nougths and crosses");
    window.setVerticalSyncEnabled(true); // call it once, after creating the window
    window.setFramerateLimit(60); // call it once, after creating the window

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(50.f, 50.f);

    shape.setOutlineThickness(10.f);
    shape.setOutlineColor(sf::Color::White);

    sf::Texture xTexture;
    if (!xTexture.loadFromFile("../images/x_2.png")) {
        std::cout << "Error" << std::endl;
        return;
    }

    sf::Texture oTexture;
    if (!oTexture.loadFromFile("../images/O.png")) {
        std::cout << "Error" << std::endl;
        return;
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //window.clear(sf::Color{0x993300});
        window.clear(sf::Color::White);
        for (int i = 1; i < 3; ++i) {

            sf::RectangleShape line(sf::Vector2f(14.f, 600.f));
            line.setFillColor(sf::Color::Black);
            line.setPosition(200.f * i, 0.f);
            window.draw(line);

            line.setSize(sf::Vector2f(600.f, 14.f));
            line.setFillColor(sf::Color::Black);
            line.setPosition(0.f, 200.f * i);
            window.draw(line);
        }

        sf::Sprite xSprite(xTexture);
        xSprite.setColor(sf::Color::White);
        xSprite.setPosition(15,15);
        xSprite.setScale(0.75f, 0.75f); // Adjust the scale as needed

        sf::Sprite oSprite(oTexture);
        oSprite.setColor(sf::Color::White);
        oSprite.setPosition(100,100);
        oSprite.setScale(0.75f, 0.75f); // Adjust the scale as needed

        window.draw(xSprite);
        window.draw(oSprite);
        window.display();
    }
}
