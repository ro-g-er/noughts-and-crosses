#ifndef NOUGHTS_AND_CROSSES_GAME_H
#define NOUGHTS_AND_CROSSES_GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Mouse.hpp>
#include <array>

class Game {
private:
    void render();
    void processEvents();
    sf::RenderWindow window;
    std::array<sf::RectangleShape, 4> grid;
    sf::CircleShape oShape;
    std::array<sf::RectangleShape, 2> xShape;
    sf::Font font;
    std::array<sf::Text, 3> menuText;
    void drawMenu();
    void drawGame();
    enum class GameState { MENU, PLAYING, GAME_OVER } gameState;
    void handleMenuInput(sf::Mouse::Button button);
public:
    Game();
    void run();
};

#endif //NOUGHTS_AND_CROSSES_GAME_H
