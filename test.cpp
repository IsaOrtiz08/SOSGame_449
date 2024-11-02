#include "gtest/gtest.h"
#include "../SOSGame_449/game_logic.h"

using namespace SOS;
// Board Size Tests
TEST(GameLogicTest, BoardSizeLessThanThree) {
    SOS::SimpleGameLogic gameLogic(2); 
    EXPECT_TRUE(gameLogic.GameDone) << "Expected GameDone to be true for board sizes less than 3";
}

TEST(GameLogicTest, BoardSizeGreaterThanTwenty) {
    SOS::SimpleGameLogic gameLogic(20);
    EXPECT_TRUE(gameLogic.GameDone) << "Expected GameDone to be true for board sizes greater than 20";
}

TEST(GameLogicTest, AcceptableBoardSize) {
    SOS::SimpleGameLogic gameLogic(10);
    EXPECT_FALSE(gameLogic.GameDone) << "Expected GameDone to be false for acceptable board size";
}


TEST(GameLogicTest, NullBoardSize) {
    SOS::SimpleGameLogic gameLogic(NULL);
    EXPECT_TRUE(gameLogic.GameDone) << "Expected GameDone to be true as it was never able to successfully begin";
}


// New Game tests
TEST(GameLogicTest, NewGameSimple) {
    SOS::SimpleGameLogic gameLogic(4);
    EXPECT_TRUE(gameLogic.gameMode == 0) << "Expected GameMode to be Simple when creating a simple game";
}

TEST(GameLogicTest, NewGameGeneral) {
    SOS::GeneralGameLogic gameLogic(4);
    EXPECT_TRUE(gameLogic.gameMode == 1) << "Expected GameMode to be General when creating a general game";
}

// Simple Game Movement
TEST(GameLogicTest, Simple_Place_S) {
    SOS::SimpleGameLogic gameLogic(4);
    gameLogic.makeMove(0, 2, "S");
    EXPECT_TRUE(gameLogic.Board[0][2] == "S") << "Expected position to contain S";
}

TEST(GameLogicTest, Simple_Place_O) {
    SOS::SimpleGameLogic gameLogic(4);
    gameLogic.makeMove(0, 2, "O");
    EXPECT_TRUE(gameLogic.Board[0][2] == "O") << "Expected position to contain O";
}

TEST(GameLogicTest, InvalidPlacement) {
    SOS::SimpleGameLogic gameLogic(4);    
    EXPECT_FALSE(gameLogic.makeMove(0, 6, "S")) << "Expected makeMove to return False for invalid move";
}

// Simple Game Winning Tests
TEST(GameLogicTest, SimpleGameEnd_P1) {
    SOS::SimpleGameLogic gameLogic(3);
    gameLogic.makeMove(0, 0, "S"); // player 1 move #1
    gameLogic.makeMove(1, 1, "S"); // player 2 move (not important)
    gameLogic.makeMove(0, 1, "O"); //player 1 move #2
    gameLogic.makeMove(1, 0, "S");
    gameLogic.makeMove(0, 2, "S");// player 1 winning move #3
    EXPECT_TRUE(gameLogic.GameDone) << "Expected true for simple game to end";
}

TEST(GameLogicTest, SimpleGameEnd_P2) {
    SOS::SimpleGameLogic gameLogic(3);
    gameLogic.makeMove(1, 1, "S"); // player 1 move (not important)
    gameLogic.makeMove(0, 0, "S"); // player 2 move #1
    gameLogic.makeMove(1, 0, "S"); 
    gameLogic.makeMove(0, 1, "O");// player 2 move #2
    gameLogic.makeMove(1, 2, "S");
    gameLogic.makeMove(0, 2, "S");// player 1 winning move #3
    EXPECT_TRUE(gameLogic.GameDone) << "Expected true for simple game to end";
}

//General Game Movement
TEST(GameLogicTest, General_Place_S) {
    SOS::GeneralGameLogic gameLogic(4);
    gameLogic.makeMove(0, 2, "S");
    EXPECT_TRUE(gameLogic.Board[0][2] == "S") << "Expected position to contain S";
}

TEST(GameLogicTest, General_Place_O) {
    SOS::GeneralGameLogic gameLogic(4);
    gameLogic.makeMove(0, 2, "O");
    EXPECT_TRUE(gameLogic.Board[0][2] == "O") << "Expected position to contain O";
}

TEST(GameLogicTest, ComputerMove) {
    SOS::GeneralGameLogic gameLogic(4);
    gameLogic.SetNextPlayer();
    gameLogic.makeMoveComputer();
    EXPECT_TRUE(gameLogic.Board[gameLogic.getLastMoveRow()][gameLogic.getLastMoveCol()] == gameLogic.getComputerLetter()) << "Expected computer move to match on Board";
}
// General Game winning tests

TEST(GameLogicTest, GeneralGameEnd) {
    SOS::GeneralGameLogic gameLogic(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameLogic.makeMove(i, j, "S");
        }
    }
    EXPECT_TRUE(gameLogic.GameDone) << "Expected True for game board being full";
}

TEST(GameLogicTest, StartSimpleGameMode) {
    // Simple game mode is typically represented by mode 1
    int board_size = 5;
    int game_mode = 1; // Assuming 1 means Simple Game Mode

    SOS::SimpleGameLogic game(board_size);

    EXPECT_EQ(game.gameMode, 1); // Assuming a getter for game mode is available
    EXPECT_FALSE(game.IsGameEnded()); // Game should be started, not done
}

// Test for AC 2.2: Choosing General Game
TEST(GameLogicTest, StartGeneralGameMode) {
    // General game mode is typically represented by mode 2
    int board_size = 5;
    int game_mode = 2; // Assuming 2 means General Game Mode

    SOS::GeneralGameLogic game(board_size);

    EXPECT_EQ(game.gameMode, 2); // Assuming a getter for game mode is available
    EXPECT_FALSE(game.IsGameEnded()); // Game should be started, not done
}

