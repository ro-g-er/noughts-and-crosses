#include "GameTests.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

TEST_F(GameTests, resetGame) {
    game.resetGame();
    ASSERT_EQ(game.getIsXTurn(), true);
    ASSERT_EQ(game.getGameState(), GameState::MENU);
    ASSERT_EQ(game.getTurnNumber(), 0);
}

TEST_F(GameTests, checkWinConditionGameNotStarted) {
    ASSERT_EQ(getCheckWinCondition(), Winner::NONE);
}

TEST_F(GameTests, checkWinConditionXWinHorizontal) {
    boardTest.at(0).fill(Mark::X);
    setBoard(boardTest);
    ASSERT_EQ(getCheckWinCondition(), Winner::X);
}
