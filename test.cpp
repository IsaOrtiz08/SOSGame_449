#include "pch.h"
#include "../SOSGame_449/game_logic.h"

using namespace SOS;

class GameLogicTest : public ::testing::Test {
protected:
    GameLogic game; // Instance of GameLogic to be used in tests

    // Reset game state before each test
    void SetUp() override {
        game.GameDone = false;
    }
};

TEST_F(GameLogicTest, TestBoardSizeGreaterThan3x3) {
    // Given
    int inputBoardSize = 4; // Input board size greater than 3x3

    // When
    game.GetBoardSize(inputBoardSize);  // Set the board size
    auto board = game.CreateBoard();    // Create the board with the given size

    // Then
    // Check that the board has been created with the correct size
    EXPECT_EQ(board.size(), inputBoardSize);
    EXPECT_EQ(board[0].size(), inputBoardSize);

    // Check that the game has started
    EXPECT_FALSE(game.GameDone);  // Game should not be done when it starts
}