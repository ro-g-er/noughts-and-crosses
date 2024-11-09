#ifndef NOUGHTS_AND_CROSSES_GAMETESTS_H
#define NOUGHTS_AND_CROSSES_GAMETESTS_H

#include "../src/Game.h"
#include <gtest/gtest.h>

class GameTests : public ::testing::Test {
protected:
    Game game;
    std::array<std::array<Mark, numRows>, numColumns> boardTest{};
    void SetUp() override {
    }

    void TearDown() override {
    }

    Winner getCheckWinCondition() { return game.checkWinCondition(); };

    void setBoard(std::array<std::array<Mark, numRows>, numColumns> b) {
        game.board = b;
    }
};

#endif//NOUGHTS_AND_CROSSES_GAMETESTS_H
