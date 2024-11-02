#pragma once
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <string>
#include <vector>
#include <iostream>

namespace SOS {

class GameLogic {
protected:
    int board_size;
    int player1 = 1, player2 = 2; // player 2 in general is the computer
    int currentPlayer = 1;
    const std::string s = "S";
    const std::string o = "O";
    std::string p1curr_letter = "";
    std::string p2curr_letter = "";
    int player1Score = 0, player2Score = 0;   
public:
    std::vector<std::pair<int, int>> completedSOSPositions;
    int gameMode; //gamemode 0: simple, gamemode 1: general
    GameLogic(int size, int mode);
    std::vector<std::vector<std::string>> Board;
    bool GameDone = false;
    int getPlayer1Score();
    int getPlayer2Score();
    std::string get_p1curr_letter();
    std::string get_p2curr_letter();
    void SetP1CurrLetter(std::string letter);
    void SetP2CurrLetter(std::string letter);
    int getCurrentPlayer();
    bool GetBoardSize(int input);
    std::vector<std::vector<std::string>> CreateBoard();
    bool IsBoardFull();
    void SetNextPlayer();
    int CheckForSOS(int row, int col);
    bool makeMove(int row, int col, const std::string& letter);
    virtual bool IsGameEnded() = 0;
    const std::vector<std::pair<int, int>>& getCompletedSOSPositions();
    void clearCompletedSOS();
};

class SimpleGameLogic : public GameLogic {
public:
    SimpleGameLogic(int size) : GameLogic(size, 0) {}

    // Override specific methods if needed
    bool IsGameEnded();
};

class GeneralGameLogic : public GameLogic {
public:
    GeneralGameLogic(int size) : GameLogic(size, 1) {}

    // Override specific methods for general mode
    bool makeMoveComputer();
    bool IsGameEnded();
    int getLastMoveCol() const;
    int getLastMoveRow() const;
    std::string getComputerLetter() const;
private:
    int computer_row, computer_column;
     int lastMoveRow;
    int lastMoveCol;
};


}
#endif // GAME_LOGIC_H
