#ifndef NOUGHTS_AND_CROSSES_GAME_H
#define NOUGHTS_AND_CROSSES_GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Mouse.hpp>
#include <array>

constexpr int numRows = 3;
constexpr int numColumns = 3;

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
    /**
     * @brief Handles player input during the game.
     * @param button The mouse button that was pressed.
     */
    void handlePlayerInput(sf::Mouse::Button button);
    /**
     * @brief Handles the action associated with the given menu index selected.
     * @param index The index of the menu item.
     */
    void handleMenuSelection(int i);
    /**
     * @brief Checks the win condition for the game.
     * @return The winning character ('X' or 'O') if there's a winner, otherwise ' '.
     */
    char checkWinCondition();
    /**
     * @brief Checks if three characters are the same and not empty.
     * @param a First character.
     * @param b Second character.
     * @param c Third character.
     * @return true if all three characters are the same and not empty, false otherwise.
     */
    static bool checkLine(char a, char b, char c);
    /**
     * @brief Checks all columns for a win condition.
    * @return The winning character ('X' or 'O') if there's a winner, otherwise ' '.
     */
    char checkColumns();
    /**
     * @brief Checks all rows for a win condition.
     * @return The winning character if any row has a win condition, otherwise ' '.
     */
    char checkRows();
    /**
     * @brief Checks both diagonals for a win condition.
     * @return true if any diagonal has a win condition, false otherwise.
     */
    char checkDiagonals();
    static void displayWinner(char w);
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
    char winner; /* 'X', 'O' and 'D' (for Draw) */
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
