#ifndef NOUGHTS_AND_CROSSES_GAME_H
#define NOUGHTS_AND_CROSSES_GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Mouse.hpp>
#include <array>

/**
 * @brief Class representing the Noughts and Crosses game.
 */
class Game {
private:
    /**
     * @brief Processes input events.
     */
    void processEvents();
    /**
     * @brief Renders the game to the window.
     */
    void render();
    /**
     * @brief Draws the main menu.
     */
    void drawMenu();
    /**
     * @brief Draws the game board and pieces.
     */
    void drawGame();
    /**
     * @brief Handles input in the menu.
     * @param button The mouse button that was pressed.
     */
    void handleMenuInput(sf::Mouse::Button button);
    /**
    * @brief Enum representing the different states of the game.
    */
    enum class GameState { MENU, PLAYING, GAME_OVER } gameState;
    sf::RenderWindow window;
    std::array<sf::RectangleShape, 4> grid;
    sf::CircleShape oShape;
    std::array<sf::RectangleShape, 2> xShape;
    sf::Font font;
    std::array<sf::Text, 3> menuText;
public:
    /**
     * @brief Constructs a Game object and set up grid and shapes.
     */
    Game();
    /**
     * @brief Runs the game loop.
     */
    void run();
};

#endif //NOUGHTS_AND_CROSSES_GAME_H
