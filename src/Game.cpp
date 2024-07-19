#include <iostream>
#include <SFML/Window/Event.hpp>
#include "Game.h"

Game::Game() : window(sf::VideoMode(600, 600), "Noughts and Crosses"),
                    isXTurn(true),
                    gameOver(false),
                    gameState(GameState::MENU) {

    window.setFramerateLimit(60);
    loadFont();
    setupGrid();
    setupShapes();
    setupMenuText();
    initializeBoard();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if (gameState == GameState::MENU) {
                handleMenuInput(event.mouseButton.button);
            } else if (gameState == GameState::PLAYING) {
                //handlePlayerInput(event.mouseButton.button, true);
            }
        }
    }
}

void Game::render() {
    window.clear(sf::Color(220, 220, 220));
    switch (gameState) {
        case GameState::MENU:
            drawMenu();
            break;
        case GameState::PLAYING:
            drawGame();
            break;
        case GameState::GAME_OVER:
            // Draw game over screen or message
            break;
    }
    window.display();
}

void Game::handleMenuInput(sf::Mouse::Button button) {
    if (button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); /* specifically designed for handling 2D integer */
        for (int i = 0; i < 3; ++i) {
            if (menuText[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                if (i == 0) { /* Start Game */
                    gameState = GameState::PLAYING;
                } else if (i == 2) { /* Exit */
                    window.close();
                }
            }
        }
    }
}

void Game::drawMenu() {
    for (const auto& text : menuText) {
        window.draw(text);
    }
}

void Game::drawGame() {
    // Draw grid
    for (auto &line: grid) {
        window.draw(line);
    }
    // Draw shapes on the board
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board.size(); ++col) {
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

void Game::resetGame() {
    initializeBoard(); // Reset the board using the initializeBoard method
    isXTurn = true;
    gameOver = false;
}

void Game::initializeBoard() {
    for (auto& row : board) {
        row.fill(' ');
    }
}

void Game::setupGrid() {
    // vertical grid lines
    for (int i = 0; i < 2; ++i) {
        grid[i].setFillColor(sf::Color(64, 64, 64));  // Dark Gray
        grid[i].setSize(sf::Vector2f(10.f, 600.f));
        grid[i].setPosition(200.f * ((float) i + 1) - 5, 0.f);
    }

    // horizontal grid lines
    for (int i = 2; i < 4; ++i) {
        grid[i].setFillColor(sf::Color(64, 64, 64));  // Dark Gray
        grid[i].setSize(sf::Vector2f(600.f, 10.f));
        grid[i].setPosition(0.f, 200.f * ((float) i - 1) - 5);
    }
}

void Game::setupShapes() {
    oShape.setRadius(80.f);
    oShape.setFillColor(sf::Color::Transparent);
    oShape.setOutlineColor(sf::Color(0, 0, 139));  // Dark Blue
    oShape.setOutlineThickness(10.f);
    for (auto & i : xShape) {
        i.setSize(sf::Vector2f(160.f, 10.f));
        i.setFillColor(sf::Color::Black);
        i.setOrigin(80.f, 5.f);
    }
}

void Game::loadFont() {
    if (!font.loadFromFile("../src/ethn.otf")) {
        throw std::runtime_error("Error loading font");
    } else {
        std::cout << "Font loaded successfully" << std::endl;
    }
}

void Game::setupMenuText() {
    std::array<std::string, 3> menuItems = { "Start Game", "Instructions", "Exit" };
    for (int i = 0; i < 3; ++i) {
        menuText[i].setFont(font);
        menuText[i].setString(menuItems[i]);
        menuText[i].setCharacterSize(30);
        menuText[i].setFillColor(sf::Color::Black);
        menuText[i].setPosition(200.f, 150.f + (float) i * 50.f);
    }
}
