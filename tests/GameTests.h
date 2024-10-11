#ifndef NOUGHTS_AND_CROSSES_GAMETESTS_H
#define NOUGHTS_AND_CROSSES_GAMETESTS_H

#include "../src/Game.h"
#include <gtest/gtest.h>

class GameTests : public ::testing::Test {
protected:
    Game game;
    void SetUp() override {
    }

    void TearDown() override {
    }
};


#endif//NOUGHTS_AND_CROSSES_GAMETESTS_H
