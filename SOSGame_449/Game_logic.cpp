//Game_logic.cpp

#include <iostream>
#include <string>
#include <vector>
#include "game_logic.h"

namespace SOS {

    int GameLogic::getPlayer1Score(){
        return player1Score;
    }

    int GameLogic::getPlayer2Score(){
        return player2Score;
    }

    std::string GameLogic::get_p1curr_letter(){
        return p1curr_letter;
    }

    std::string GameLogic::get_p2curr_letter(){
        return p2curr_letter;
    }

    void GameLogic::SetP1CurrLetter(std::string letter){
        if (letter == "S")
            p1curr_letter = s;
        else if (letter == "O")
            p1curr_letter = o;
    }

    void GameLogic::SetP2CurrLetter(std::string letter){
        if (letter == "S")
            p2curr_letter = s;
        else if (letter == "O")
            p2curr_letter = o;
    }

    int GameLogic::getCurrentPlayer(){
        return currentPlayer;
    }

    void GameLogic::GetBoardSize(int input) {
        int size = input;
        std::string error_large_board_size = "Invalid board size. Cannot exceed board larger than 15x15. Please try again";
        std::string error_small_board_size = "Invalid board size. Board must be larger than 2x2. Please try again.";
        if (size > 15) {
            std::cout << error_large_board_size << std::endl;
            GetBoardSize(input);
        }
        else if (size < 3) {
            std::cout << error_small_board_size << std::endl;
            GetBoardSize(input);
        }
        else {
            board_size = size;
        }
    }

    std::vector<std::vector<std::string>> GameLogic::CreateBoard() {
        std::vector<std::vector<std::string>> board(board_size, std::vector<std::string>(board_size, ""));
        Board = board;
        return Board;
    }

    bool GameLogic::IsBoardFull() {
        for (int i = 0; i < board_size; i++) {
            for (int j = 0; j < board_size; j++) {
                if (Board[i][j] == "") {
                    return false;
                }
            }
        }
        return true;
    }

    void GameLogic::ChooseGameMode(int input) {
        if (input == 0) {
            gameMode = 0;
        }
        else if (input == 1) {
            gameMode = 1;
        }
        else {

        }
    }

    void GameLogic::SetNextPlayer() {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }


    int GameLogic::CheckForSOS(int row, int col) {
        int sosCount = 0;

        //horizontal check
        if (col >= 1 && col <= board_size - 2 && Board[row][col - 1] == s && Board[row][col + 1] == s && Board[row][col] == o) {
            sosCount++;
        }

        //vertical check
        if (row >= 1 && row <= board_size - 2 && Board[row - 1][col] == s && Board[row + 1][col] == s && Board[row][col] == o) {
            sosCount++;
        }

        // Diagonal check (top-left to bottom-right)
        if (row >= 1 && row <= board_size - 2 && col >= 1 && col <= board_size - 2 &&
            Board[row - 1][col - 1] == s && Board[row + 1][col + 1] == s && Board[row][col] == o) {
            sosCount++;
        }

        // Diagonal check (top-right to bottom-left)
        if (row >= 1 && row <= board_size - 2 && col >= 1 && col <= board_size - 2 &&
            Board[row - 1][col + 1] == s && Board[row + 1][col - 1] == s && Board[row][col] == o) {
            sosCount++;
        }

        return sosCount;
    }

    // Make a move on the board
    bool GameLogic::makeMove(int row, int col, const std::string& letter) {
        if (row < 0 || row >= board_size || col < 0 || col >= board_size || (letter != "S" && letter != "O")) {
            std::cout << "Invalid move. Try again.\n";
            return false;
        }
        if (Board[row][col] != "") {
            std::cout << "Cell already taken. Choose another.\n";
            return false;
        }

        // Place the letter on the board
        Board[row][col] = letter;

        // Check if the move forms any "SOS" patterns
        int sosCount = CheckForSOS(row, col);
        if (sosCount > 0) {
            std::cout << "SOS count: " << sosCount << std::endl;
            if (currentPlayer == 1) {
                player1Score += sosCount;
                std::cout << "Player 1 score: " << player1Score << std::endl;
            }
            else {
                player2Score += sosCount;
                            std::cout << "Player 2 score: " << player2Score << std::endl;
        }
        }

        // Switch players
        std::cout << player1Score << " " << player2Score << std::endl;
        SetNextPlayer();
        return true;
    }


    bool GameLogic::IsGameEnded_Simple() {
        std::string player1wins = "Player 1 Wins!";
        std::string player2wins = "Player 2 Wins!";
        std::string draw = "Draw!";

        // draw if both players have the same score and an SOS has been made
        if (player1Score == player2Score && player1Score >= 1 && player2Score >= 1) {
            std::cout << draw << std::endl;
            return true;
        }
        // player1 wins if they scored a point
        if (player1Score >= 1) {
            std::cout << player1wins << std::endl;
            return true;
        }
        // player 2 wins if they scored a point
        if (player2Score >= 1) {
            std::cout << player2wins << std::endl;
            return true;
        }
        // no points made, continue game
        else
            return false;
    }

    bool GameLogic::IsGameEnded_General() {
        std::string playerwins = "You Win!";
        std::string computerwins = "Computer Wins!";
        std::string draw = "Draw!";
        // check if every spot on the board is occupied
        if (!IsBoardFull())
            return false;
        // draw if both players have the same score
        if (player1Score == player2Score) {
            std::cout << draw << std::endl;
            return true;
        }
        // player1 wins if score is higher
        if (player1Score >= player2Score) {
            std::cout << playerwins << std::endl;
            return true;
        }
        // computer wins if score is higher
        if (player2Score >= player1Score) {
            std::cout << computerwins << std::endl;
            return true;
        }
        // no points made, continue game
        else
            return false;
    }
};
