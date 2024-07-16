#include "game.h"

Game::Game() : window(sf::VideoMode(600, 600), "Noughts and Crosses") {
    window.setFramerateLimit(60);

    // Set up vertical grid lines
    for (int i = 0; i < 2; ++i) {
        grid[i].setFillColor(sf::Color(64, 64, 64));  // Dark Gray
        grid[i].setSize(sf::Vector2f(10.f, 600.f));
        grid[i].setPosition(200.f * ((float) i + 1) - 5, 0.f);
    }

    // Set up horizontal grid lines
    for (int i = 2; i < 4; ++i) {
        grid[i].setFillColor(sf::Color(64, 64, 64));  // Dark Gray
        grid[i].setSize(sf::Vector2f(600.f, 10.f));
        grid[i].setPosition(0.f, 200.f * ((float) i - 1) - 5);
    }

    // Set up shapes
    oShape.setRadius(80.f);
    oShape.setFillColor(sf::Color::Transparent);
    oShape.setOutlineColor(sf::Color::Black);
    oShape.setOutlineColor(sf::Color(0, 0, 139));  // Dark Blue
    oShape.setOutlineThickness(10.f);

    for (auto & i : xShape) {
        i.setSize(sf::Vector2f(160.f, 10.f));
        i.setFillColor(sf::Color::Black);
        i.setOrigin(80.f, 5.f);
    }
}

void Game::run() {
    while (window.isOpen()) {
        render();
    }
}

void Game::render() {
    window.clear(sf::Color(245, 245, 220));  // Light Beige

    // Draw grid
    for (auto &i: grid) {
        window.draw(i);
    }

    // Draw shapes on the board
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            oShape.setPosition((float) col * 200.f + 20.f, (float) row * 200.f + 20.f);
            window.draw(oShape);
            xShape[0].setPosition((float) col * 200.f + 100.f, (float) row * 200.f + 100.f);
            xShape[0].setRotation(45.f);

            xShape[1].setPosition((float) col * 200.f + 100.f, (float) row * 200.f + 100.f);
            xShape[1].setRotation(135.f);
            window.draw(xShape[0]);
            window.draw(xShape[1]);
        }
    }
    window.display();
}