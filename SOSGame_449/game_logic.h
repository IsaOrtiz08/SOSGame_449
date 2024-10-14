#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <string>
#include <vector>
#include <iostream>

namespace SOS {

class GameLogic {
private:
    int board_size;
    std::vector<std::vector<std::string>> Board;
    int player1 = 1, player2 = 2;
    int currentPlayer = 1;
    const std::string s = "S";
    const std::string o = "O";
    std::string p1curr_letter = "";
    std::string p2curr_letter = "";
    int player1Score = 0, player2Score = 0;
    int gameMode = 0; //gamemode 0: simple, gamemode 1: general
public:
    bool GameDone = false;
    int getPlayer1Score();
    int getPlayer2Score();
    std::string get_p1curr_letter();
    std::string get_p2curr_letter();
    void SetP1CurrLetter(std::string letter);
    void SetP2CurrLetter(std::string letter);
    int getCurrentPlayer();
    void GetBoardSize(int input);
    std::vector<std::vector<std::string>> CreateBoard();
    bool IsBoardFull();
    void ChooseGameMode(int input);
    void SetNextPlayer();
    int CheckForSOS(int row, int col);
    // Make a move on the board
    bool makeMove(int row, int col, const std::string& letter);
    bool IsGameEnded_Simple();
    bool IsGameEnded_General();
};

}
#endif // GAME_LOGIC_H
