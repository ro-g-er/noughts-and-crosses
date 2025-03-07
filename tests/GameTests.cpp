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

TEST_F(GameTests, checkWinConditionXWinHorizontalTop) {
    boardTest.at(0).fill(Mark::X);
    setBoard(boardTest);
    ASSERT_EQ(getCheckWinCondition(), Winner::X);
}

TEST_F(GameTests, checkWinConditionXWinHorizontalMiddle) {
    boardTest.at(1).fill(Mark::X);
    setBoard(boardTest);
    ASSERT_EQ(getCheckWinCondition(), Winner::X);
}

TEST_F(GameTests, checkWinConditionXWinHorizontalBottom) {
    boardTest.at(2).fill(Mark::X);
    setBoard(boardTest);
    ASSERT_EQ(getCheckWinCondition(), Winner::X);
}


TEST_F(GameTests, checkWinConditionOWinVerticalLeft) {
    for (auto &row: boardTest) {
        row[0] = Mark::O;
    }
    setBoard(boardTest);
    ASSERT_EQ(getCheckWinCondition(), Winner::O);
}

TEST_F(GameTests, checkWinConditionXWinVerticalMiddle) {
    for (auto &row: boardTest) {
        row[1] = Mark::X;
    }
    setBoard(boardTest);
    ASSERT_EQ(getCheckWinCondition(), Winner::X);
}

TEST_F(GameTests, checkWinConditionOWinVerticalRight) {
    for (auto &row: boardTest) {
        row[2] = Mark::O;
    }
    setBoard(boardTest);
    ASSERT_EQ(getCheckWinCondition(), Winner::O);
}

TEST_F(GameTests, checkWinConditionXWinDiagonalTopLeftToBottomRight) {
    for (size_t i = 0; i < boardTest.size(); ++i) {
        boardTest[i][i] = Mark::X;
    }
    setBoard(boardTest);
    ASSERT_EQ(getCheckWinCondition(), Winner::X);
}

TEST_F(GameTests, checkWinConditionOWinDiagonalTopRightToBottomLeft) {
    for (size_t i = 0; i < boardTest.size(); ++i) {
        boardTest[i][boardTest.size() - 1 - i] = Mark::O;
    }
    setBoard(boardTest);
    ASSERT_EQ(getCheckWinCondition(), Winner::O);
}
