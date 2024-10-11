#include "GameTests.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

TEST_F(GameTests, resetGame) {
    game.resetGame();
    ASSERT_EQ(game.getIsXTurn(), true);
    ASSERT_EQ(game.getGameState(), GameState::MENU);
    ASSERT_EQ(game.getTurnNumber(), 0);
}
