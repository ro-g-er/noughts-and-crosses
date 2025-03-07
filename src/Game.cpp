#include "Game.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <sstream>

Winner markToWinner(Mark mark) {
    Winner returnValue = Winner::NONE;
    switch (mark) {
        case Mark::X:
            returnValue = Winner::X;
            break;
        case Mark::O:
            returnValue = Winner::O;
            break;
        case Mark::EMPTY:
            returnValue = Winner::NONE;
            break;
    }
    return returnValue;
}

Game::Game() {
#ifndef TEST
    window.create(sf::VideoMode(600, 600), "Noughts and Crosses");
    window.setFramerateLimit(60);
#endif
    loadFont();
    setupGrid();
    setupShapes();
    setupMenuText();
    setupInstructionsText();
    initializeBoard();
    gameState = GameState::MENU;
    winner = Winner::NONE;
    isXTurn = true;
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
            } else if (gameState == GameState::GAME_OVER) {
                handleGameOver(event.mouseButton.button);
            } else if (gameState == GameState::INSTRUCTIONS) {
                handleInstructions(event.mouseButton.button);
            }
        }
    }
}

void Game::render() {
    window.clear(sf::Color(18, 18, 18));//220
    switch (gameState) {
        case GameState::MENU:
            drawMenu();
            break;
        case GameState::INSTRUCTIONS:
            drawInstructions();
            break;
        case GameState::PLAYING:
            drawGame();
            break;
        case GameState::GAME_OVER:
            drawWinner();
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
            gameState = GameState::INSTRUCTIONS;
            break;
        case 2: /* Exit */
            window.close();
            break;
        default:
            break;
    }
}

void Game::drawMenu() {
    for (const auto &text: menuText) {
        window.draw(text);
    }
}

void Game::drawGame() {
    for (const auto &line: grid) {
        window.draw(line);
    }
    // Draw shapes on the board
    for (int row = ROW_1; row < board.size(); ++row) {
        for (int col = COL_1; col < board.at(COL_1).size(); ++col) {
            if (board[row][col] == Mark::X) {
                xShape[0].setPosition((float) col * 200.f + 100.f, (float) row * 200.f + 100.f);
                xShape[1].setPosition((float) col * 200.f + 100.f, (float) row * 200.f + 100.f);
                window.draw(xShape.at(0));
                window.draw(xShape.at(1));
            } else if (board[row][col] == Mark::O) {
                oShape.setPosition((float) col * 200.f + 25.f, (float) row * 200.f + 25.f);
                window.draw(oShape);
            }
        }
    }
    window.display();
}

void Game::resetGame() {
    initializeBoard(); /* Reset the board */
    isXTurn = true;
    gameState = GameState::MENU;
    turnNumber = 0;
}

void Game::initializeBoard() {
    for (auto &row: board) {
        row.fill(Mark::EMPTY);
    }
}

void Game::setupGrid() {
    // vertical grid lines
    for (int i = 0; i < 2; ++i) {
        grid[i].setFillColor(sf::Color(47, 79, 79));// 64
        grid[i].setSize(sf::Vector2f(10.f, 600.f));
        grid[i].setPosition(200.f * ((float) i + 1) - 5, 0.f);
    }
    // horizontal grid lines
    for (int i = 2; i < 4; ++i) {
        grid[i].setFillColor(sf::Color(47, 79, 79));// 64
        grid[i].setSize(sf::Vector2f(600.f, 10.f));
        grid[i].setPosition(0.f, 200.f * ((float) i - 1) - 5);
    }
}

void Game::setupShapes() {
    oShape.setRadius(75.f);
    oShape.setFillColor(sf::Color::Transparent);
    oShape.setOutlineColor(sf::Color(192, 192, 192));// Dark Blue - 0.0.139
    oShape.setOutlineThickness(10.f);
    for (auto &i: xShape) {
        i.setSize(sf::Vector2f(160.f, 10.f));
        i.setFillColor(sf::Color(192, 192, 192));//Black
        i.setOrigin(80.f, 5.f);
    }
    xShape[0].setRotation(45.f);
    xShape[1].setRotation(135.f);
}

void Game::loadFont() {
    std::vector<std::string> paths = {
            "../resources/ethn.otf",   // Local path
            "../../resources/ethn.otf",// Test path
            "./resources/ethn.otf"     // GitHub Actions or other CI environments
    };
    for (const auto &path: paths) {
        if (font.loadFromFile(path)) {
            std::cout << "Font loaded successfully from " << path << std::endl;
            return;
        }
    }
    throw std::runtime_error("Error loading font: File not found in any specified path.");
}

void Game::setupMenuText() {
    std::array<std::string, 3> menuItems = {"Start Game", "Instructions", "Exit"};
    for (int i = 0; i < menuText.size(); i++) {
        menuText[i].setFont(font);
        menuText[i].setString(menuItems[i]);
        menuText[i].setCharacterSize(30);
        menuText[i].setFillColor(sf::Color(211, 211, 211));//Black
        menuText[i].setPosition(MENU_X_POS, MENU_START_Y + (MENU_OFFSET_Y * (float) i));
    }
}

void Game::setupGameOver() {
    std::stringstream menuItems;
    if (winner == Winner::X || winner == Winner::O) {
        menuItems << "THE WINNER IS: " << static_cast<char>(winner);
    } else {
        menuItems << "IT IS A DRAW";
    }
    gameOverText.setFont(font);
    gameOverText.setString(menuItems.str());
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color(255, 255, 255));
    gameOverText.setPosition(100.f, 150.f + 50.f);
}

void Game::handlePlayerInput(sf::Mouse::Button button) {
    if (button != sf::Mouse::Left || gameState != GameState::PLAYING) {
        return;
    }
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int row = mousePos.y / 200;
    int col = mousePos.x / 200;
    if (row >= numRows || col >= numColumns || board[row][col] != Mark::EMPTY) {
        return;
    }
    board[row][col] = isXTurn ? Mark::X : Mark::O;
    turnNumber++;
    isXTurn = !isXTurn;
    if (turnNumber > WINNING_TURN_THRESHOLD) {
        winner = checkWinCondition();
        if (winner != Winner::NONE) {
            gameState = GameState::GAME_OVER;
        }
    }
}

Winner Game::checkWinCondition() {
    winner = checkRows();
    if (winner != Winner::NONE) {
        return winner;
    }
    winner = checkColumns();
    if (winner != Winner::NONE) {
        return winner;
    }
    winner = checkDiagonals();
    if (winner != Winner::NONE) {
        return winner;
    }
    if (turnNumber == MAX_TURNS) {
        return Winner::DRAW;
    }
    return winner;
}

Winner Game::checkRows() const {
    for (const auto &row: board) {
        if (checkLine(row[ROW_1], row[ROW_2], row[ROW_3])) {
            return markToWinner(row[ROW_1]);
        }
    }
    return Winner::NONE;
}

Winner Game::checkColumns() {
    for (int col = COL_1; col < numColumns; ++col) {
        if (checkLine(board[ROW_1][col], board[ROW_2][col], board[ROW_3][col])) {
            return markToWinner(board[ROW_1][col]);
        }
    }
    return Winner::NONE;
}

bool Game::checkLine(Mark a, Mark b, Mark c) {
    return (a == b && b == c && a != Mark::EMPTY);
}

Winner Game::checkDiagonals() {
    if (checkLine(board[ROW_1][COL_1], board[ROW_2][COL_2], board[ROW_3][COL_3])) {
        return markToWinner(board[0][COL_1]);
    }
    if (checkLine(board[ROW_1][COL_3], board[ROW_2][COL_2], board[ROW_3][COL_1])) {
        return markToWinner(board[ROW_1][COL_3]);
    }
    return Winner::NONE;
}

void Game::drawWinner() {
    setupGameOver();
    window.draw(gameOverText);
}

void Game::handleGameOver(sf::Mouse::Button button) {
    if (button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); /* specifically designed for handling 2D integer */
        if (gameOverText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            resetGame();
        }
    }
}

void Game::handleInstructions(sf::Mouse::Button button) {
    if (button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); /* specifically designed for handling 2D integer */
        if (instructionsText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            gameState = GameState::MENU;
        }
    }
}

void Game::setupInstructionsText() {
    std::string instructions =
            "The goal of the game is to align three\n"
            "of your marks (X or O) in a row, column\n"
            "or diagonal before your opponent.\n\n"
            "How to Play:\n"
            "- Click on any empty square in the grid\n"
            " to place your mark.\n"
            "- The first player to align three\n"
            " of their marks in a row, column,\n"
            " or diagonal wins the game.\n"
            "- If all nine squares are filled without\n"
            " any player achieving a line,\n"
            " the game ends in a draw.\n\n"
            "Returning to Menu:\n"
            "To return to the main menu, press\n"
            "the Back button\n"
            "or the Escape key at any time.\n\n"
            "Good luck, and enjoy the game!";

    instructionsText.setFont(font);
    instructionsText.setString(instructions);
    instructionsText.setCharacterSize(18);
    instructionsText.setFillColor(sf::Color::White);// Dark Mode Color
    instructionsText.setPosition(30.f, 20.f);
    instructionsText.setLineSpacing(1.3f);
}

void Game::drawInstructions() {
    window.draw(instructionsText);
}

bool Game::getIsXTurn() const {
    return isXTurn;
}

int Game::getTurnNumber() const {
    return turnNumber;
}

GameState Game::getGameState() const {
    return gameState;
}
