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
 * @brief The number of rows on the game board.
 *
 * This constant defines the number of rows present on the game board. It is used to determine the
 * vertical dimension of the board.
 */
constexpr int numRows = 3;
/**
 * @brief The number of columns on the game board.
 *
 * This constant defines the number of columns present on the game board. It is used to determine the
 * horizontal dimension of the board.
 */
constexpr int numColumns = 3;

/**
 * @brief Index of the first row (0-based index).
 */
constexpr int ROW_1 = 0;
/**
 * @brief Index of the second row (1-based index).
 */
constexpr int ROW_2 = 1;
/**
 * @brief Index of the third row (2-based index).
 */
constexpr int ROW_3 = 2;

/**
 * @brief Index of the first column (0-based index).
 */
constexpr int COL_1 = 0;
/**
 * @brief Index of the second column (1-based index).
 */
constexpr int COL_2 = 1;
/**
 * @brief Index of the third column (2-based index).
 */
constexpr int COL_3 = 2;

/**
 * @brief The vertical starting position of menu items.
 *
 * This constant defines the vertical offset from the top of the window where the menu items will start.
 * It is used to position the menu items in a vertical arrangement.
 */
constexpr float MENU_START_Y = 200.f;
/**
 * @brief The vertical offset between consecutive menu items.
 *
 * This constant determines the spacing between the menu items. It helps in arranging the menu items
 * vertically with consistent spacing.
 */
constexpr float MENU_OFFSET_Y = 50.f;
/**
 * @brief The horizontal position of the menu items.
 *
 * This constant sets the horizontal position where the menu items will be displayed. It is used for
 * aligning the menu items horizontally in the window.
 */
constexpr float MENU_X_POS = 150.f;
/**
 * @brief The minimum number of turns required before checking for a winning condition.
 *
 * This helps to optimize the game by not checking for a win until it's possible.
 */
constexpr int WINNING_TURN_THRESHOLD = 4;
/**
 * @brief The maximum number of turns in the game, representing a full board without a winner.
 */
constexpr int MAX_TURNS = 9;

/**
 * @brief Enum representing the different states of the game.
 */
enum class GameState {
    MENU,
    INSTRUCTIONS,
    PLAYING,
    GAME_OVER
};
/**
 * @brief Enum representing the winner of the game.
 *
 * This enum is used to indicate the final outcome of the game.
 */
enum class Winner {
    X = 'X',    /**< Player X has won the game. */
    O = 'O',    /**< Player O has won the game. */
    DRAW = 'D', /**< The game ended in a draw. */
    NONE = ' '  /**< The game is still ongoing or no winner has been determined. */
};

/**
 * @brief Enum representing the state of a cell on the game board.
 *
 * This enum is used to mark each cell on the board with either X, O, or as EMPTY.
 */
enum class Mark {
    X = 'X',    /**< Cell is marked by Player X. */
    O = 'O',    /**< Cell is marked by Player O. */
    EMPTY = ' ' /**< Cell is empty and unmarked. */
};

/**
 * @brief Class representing the Noughts and Crosses game.
 */
class Game {
    /**
     * @brief Loads the font from file.
     * @throws std::runtime_error if the font cannot be loaded.
     */
    void loadFont();
    /**
     * @brief Sets up the grid lines.
     */
    void setupGrid();
    /**
     * @brief Sets up the shapes for 'X' and 'O'.
     */
    void setupShapes();
    /**
     * @brief Sets up the menu text using the loaded font.
     */
    void setupMenuText();
    /**
     * @brief Initializes the game board with empty values.
     */
    void initializeBoard();
    /**
     * @brief Processes input events.
     */
    void processEvents();
    /**
     * @brief Renders the game objects.
     */
    void render();
    /**
     * @brief Handles input in the menu.
     * @param button The mouse button that was pressed.
     */
    void handleMenuInput(sf::Mouse::Button button);

    /**
     * @brief Handles player input during the game.
     * @param button The mouse button that was pressed.
     */
    void handlePlayerInput(sf::Mouse::Button button);
    /**
     * @brief Handles game over.
     * @param button The mouse button that was pressed.
     */
    void handleGameOver(sf::Mouse::Button button);
    /**
     * @brief Handles the action associated with the given menu index selected.
     * @param index The index of the menu item.
     */
    void handleMenuSelection(int i);
    /**
     * @brief Draws the main menu.
     */
    void drawMenu();
    /**
     * @brief Draws the game board and pieces.
     */
    void drawGame();
    /**
     * @brief Display the winner or draw on screen.
     */
    void drawWinner();

    void drawInstructions();
    /**
     * @brief Sets up winner text.
     */
    void setupGameOver();
    /**
     * @brief Checks the win condition for the game.
     * @return The winner enum of the winning player or draw.
     */
    Winner checkWinCondition();
    /**
     * @brief Checks if three characters are the same and not empty.
     * @param a First character.
     * @param b Second character.
     * @param c Third character.
     * @return true if all three characters are the same and not empty, false otherwise.
     */
    static bool checkLine(Mark a, Mark b, Mark c);
    /**
     * @brief Checks all columns for a win condition.
     * @return The winner enum of the winning player.
     */
    Winner checkColumns();
    /**
     * @brief Checks all rows for a win condition.
     * @return The winner enum of the winning player.
     */
    Winner checkRows() const;
    /**
     * @brief Checks both diagonals for a win condition.
     * @return The winner enum of the winning player.
     */
    Winner checkDiagonals();

    void setupInstructionsText();

    sf::RenderWindow window;
    std::array<sf::RectangleShape, 4> grid;
    sf::CircleShape oShape;
    std::array<sf::RectangleShape, 2> xShape;
    sf::Font font;
    std::array<sf::Text, 3> menuText;
    sf::Text menuWinner;
    std::array<std::array<Mark, numRows>, numColumns> board{};
    GameState gameState;
    bool isXTurn;
    Winner winner;
    sf::Text gameOverText;
    int turnNumber = 0;
    sf::Text instructionsText;
    friend class GameTests;

public:
    /**
     * @brief Constructs a Game object and initializes the game.
     */
    Game();
    /**
     * @brief Runs the game loop.
     */
    void run();
    void handleInstructions(sf::Mouse::Button button);
    /**
     * @brief Resets the game state and board.
     */
    void resetGame();
    bool getIsXTurn() const;
    int getTurnNumber() const;
    GameState getGameState() const;
};

#endif //NOUGHTS_AND_CROSSES_GAME_H
