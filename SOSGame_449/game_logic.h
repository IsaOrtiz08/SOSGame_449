#pragma once
//#ifndef GAME_LOGIC_H
//#define GAME_LOGIC_H
#include <string>
#include <vector>
#include <iostream>

namespace SOS {

    class GameLogic {
    protected:
        int board_size;
        int player1 = 1, player2 = 2;
        int player1_mode = 0, player2_mode = 0; // mode determines human or computer player, 0 is human, 1 is computer
        int currentPlayer = 1;
        const std::string s = "S";
        const std::string o = "O";
        std::string p1curr_letter = "";
        std::string p2curr_letter = "";
        int player1Score = 0, player2Score = 0;        
        int lastMoveRow;
        int lastMoveCol;
        int computer_row = NULL, computer_column = NULL;

    public:
        std::vector<std::pair<int, int>> completedSOSPositions;
        int gameMode; //gamemode 0: simple, gamemode 1: general
        GameLogic(int size, int mode, int p1_mode, int p2_mode);
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
        bool makeMoveComputer();
        virtual bool IsGameEnded() = 0;
        const std::vector<std::pair<int, int>>& getCompletedSOSPositions();
        void clearCompletedSOS();        
        int getLastMoveCol() const;
        int getLastMoveRow() const;
        std::string getComputerLetter() const;
        void SetP1Mode(int mode);
        void SetP2Mode(int mode);
        int GetP1Mode();
        int GetP2Mode();
    };

    class SimpleGameLogic : public GameLogic {
    public:
        SimpleGameLogic(int size, int p1_mode, int p2_mode) : GameLogic(size, 0, p1_mode, p2_mode) {}
        bool IsGameEnded();
    };

    class GeneralGameLogic : public GameLogic {
    public:
        GeneralGameLogic(int size, int p1_mode, int p2_mode) : GameLogic(size, 1, p1_mode, p2_mode) {}
        bool IsGameEnded();
    };


}
//#endif // GAME_LOGIC_H
