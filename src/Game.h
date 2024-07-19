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
 * @brief Enum representing the different states of the game.
 */
enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

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
     * @brief Renders the game objects.
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
     * @brief Initializes the game board with empty values.
     */
    void initializeBoard();
    /**
     * @brief Sets up the grid lines.
     */
    void setupGrid();
    /**
     * @brief Sets up the shapes for 'X' and 'O'.
     */
    void setupShapes();
    /**
    * @brief Loads the font from file.
    * @throws std::runtime_error if the font cannot be loaded.
    */
    void loadFont();
    /**
     * @brief Sets up the menu text using the loaded font.
     */
    void setupMenuText();
    /**
     * @brief Resets the game state and board.
     */
    void resetGame();
    sf::RenderWindow window;
    std::array<sf::RectangleShape, 4> grid;
    sf::CircleShape oShape;
    std::array<sf::RectangleShape, 2> xShape;
    sf::Font font;
    std::array<sf::Text, 3> menuText;
    std::array<std::array<char, 3>, 3> board{}; // 'X', 'O', or ' '
    GameState gameState;
    bool isXTurn;
    bool gameOver;
public:
    /**
    * @brief Constructs a Game object and initializes the game.
    */
    Game();
    /**
     * @brief Runs the game loop.
     */
    void run();
};

#endif //NOUGHTS_AND_CROSSES_GAME_H
