#ifndef NOUGHTS_AND_CROSSES_GAME_H
#define NOUGHTS_AND_CROSSES_GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class Game {
private:
    void render();
    sf::RenderWindow window;
    sf::RectangleShape grid[4];
    sf::CircleShape oShape;
    sf::RectangleShape xShape[2];

public:
    Game();
    void run();
};

#endif //NOUGHTS_AND_CROSSES_GAME_H
