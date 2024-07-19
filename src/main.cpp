#include <iostream>
#include "Game.h"

int main()
{
    try {
        Game game{};
        game.run();
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to start the game: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
