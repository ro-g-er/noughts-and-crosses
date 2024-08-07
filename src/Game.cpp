#include <iostream>
#include <SFML/Window/Event.hpp>
#include "Game.h"

Game::Game() : window(sf::VideoMode(600, 600), "Noughts and Crosses"),
               gameState(GameState::MENU),
               isXTurn(true),
               gameOver(false),
               winner(Winner::DRAW) {

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
                handlePlayerInput(event.mouseButton.button);
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
            displayWinner();
            resetGame();
            break;
    }
    window.display();
}

void Game::handleMenuInput(sf::Mouse::Button button) {
    if (button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); /* specifically designed for handling 2D integer */
        for (int i = 0; i < menuText.size(); ++i) {
            if (menuText.at(i).getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                handleMenuSelection(i);
            }
        }
    }
}

void Game::handleMenuSelection(int i) {
    switch (i) {
        case 0: /* Start Game */
            gameState = GameState::PLAYING;
            break;
        case 1: /* Instructions */
            std::cout << "Instructions" << std::endl;
            break;
        case 2: /* Exit */
            window.close();
            break;
        default:
            break;
    }
}

void Game::drawMenu() {
    for (const auto& text : menuText) {
        window.draw(text);
    }
}

void Game::drawGame() {
    for (auto &line: grid) {
        window.draw(line);
    }
    // Draw shapes on the board
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board.at(0).size(); ++col) {
            if (board[row][col] == Winner::X) {
                xShape[0].setPosition((float) col * 200.f + 100.f, (float) row * 200.f + 100.f);
                xShape[1].setPosition((float) col * 200.f + 100.f, (float) row * 200.f + 100.f);
                window.draw(xShape.at(0));
                window.draw(xShape.at(1));
            } else if (board[row][col] == Winner::O) {
                oShape.setPosition((float) col * 200.f + 20.f, (float) row * 200.f + 20.f);
                window.draw(oShape);
            }
        }
    }
    window.display();
}

void Game::resetGame() {
    initializeBoard(); /* Reset the board */
    isXTurn = true;
    gameOver = false;
    gameState = (GameState::MENU);
}

void Game::initializeBoard() {
    for (auto& row : board) {
        row.fill(Winner::DRAW);
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
    xShape[0].setRotation(45.f);
    xShape[1].setRotation(135.f);
}

void Game::loadFont() {
    if (!font.loadFromFile("../resources/ethn.otf")) {
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

void Game::handlePlayerInput(sf::Mouse::Button button) {
    if (button == sf::Mouse::Left && !gameOver) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int row = mousePos.y / 200;
        int col = mousePos.x / 200;
        if (row < numRows && col < numColumns && board[row][col] == Winner::DRAW) {
            board[row][col] = isXTurn ? Winner::X : Winner::O;
            isXTurn = !isXTurn;
            winner = checkWinCondition();
            if (winner != Winner::DRAW) {
                gameOver = true;
                //displayWinner(winner);
                gameState = GameState::GAME_OVER;
            }
        }
    }
}

Winner Game::checkWinCondition() {
    winner = checkRows();
    if (winner != Winner::DRAW) {
        return winner;
    }
    winner = checkColumns();
    if (winner != Winner::DRAW) {
        return winner;
    }

    return checkDiagonals();
}

Winner Game::checkRows() {
    for (const auto &row: board) {
        if (checkLine(row[0], row[1], row[2])) {
            return row.at(0);
        }
    }
    return Winner::DRAW;
}

Winner Game::checkColumns() {
    for (int col = 0; col < 3; ++col) {
        if (checkLine(board[0][col], board[1][col], board[2][col])) {
            return board[0][col];
        }
    }
    return Winner::DRAW;
}

bool Game::checkLine(enum Winner a, enum Winner b, enum Winner c) {
    return (a == b && b == c && a != Winner::DRAW);
}

Winner Game::checkDiagonals() {
    if (checkLine(board[0][0], board[1][1], board[2][2])) {
        return board[0][0];
    }
    if (checkLine(board[0][2], board[1][1], board[2][0])) {
        return board[0][2];
    }
    return Winner::DRAW;
}

void Game::displayWinner() {
    std::string menuWinner{};
    std::string menuItems = {"The winner is: "};

    if (winner == Winner::X) {
        menuItems = menuItems + 'X';
        std::cout << "Player X wins!" << std::endl;
    } else if (winner == Winner::O) {
        std::cout << "Player O wins!" << std::endl;
    } else {
        std::cout << "It's a draw!" << std::endl;
    }
    gameoverText.setFont(font);
    gameoverText.setString(menuItems);
    gameoverText.setCharacterSize(30);
    gameoverText.setFillColor(sf::Color::Black);
    gameoverText.setPosition(200.f, 150.f + 50.f);
}
