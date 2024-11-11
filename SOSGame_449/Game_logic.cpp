//Game_logic.cpp

#include <iostream>
#include <string>
#include <vector>
#include "game_logic.h"

namespace SOS {

    GameLogic::GameLogic(int size, int mode, int p1_mode, int p2_mode) {
        board_size = size;
        gameMode = mode;
        SetP1Mode(p1_mode);
        SetP2Mode(p2_mode);
        if (GetBoardSize(size)) {
            CreateBoard();
        }
        else {
            GameDone = true;
        }
    }

    int GameLogic::getPlayer1Score() {
        return player1Score;
    }

    int GameLogic::getPlayer2Score() {
        return player2Score;
    }

    std::string GameLogic::get_p1curr_letter() {
        return p1curr_letter;
    }

    std::string GameLogic::get_p2curr_letter() {
        return p2curr_letter;
    }

    void GameLogic::SetP1CurrLetter(std::string letter) {
        if (letter == "S")
            p1curr_letter = s;
        else if (letter == "O")
            p1curr_letter = o;
    }

    void GameLogic::SetP2CurrLetter(std::string letter) {
        if (letter == "S")
            p2curr_letter = s;
        else if (letter == "O")
            p2curr_letter = o;
    }

    int GameLogic::getCurrentPlayer() {
        return currentPlayer;
    }

    bool GameLogic::GetBoardSize(int input) {
        int size = input;
        std::string error_large_board_size = "Invalid board size. Cannot exceed board larger than 15x15. Please try again";
        std::string error_small_board_size = "Invalid board size. Board must be larger than 2x2. Please try again.";
        if (size > 15) {
            std::cout << error_large_board_size << std::endl;
            return false;
        }
        else if (size < 3) {
            std::cout << error_small_board_size << std::endl;
            return false;
        }
        else {
            board_size = size;
            return true;
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


    void GameLogic::SetNextPlayer() {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }


    int GameLogic::CheckForSOS(int row, int col) {
        int sosCount = 0;
        if (Board[row][col] == s) {
            // Horizontal checks
            if (col <= board_size - 3 && Board[row][col + 1] == o && Board[row][col + 2] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row, col + 1 });
                completedSOSPositions.push_back({ row, col + 2 });
            }
            if (col >= 2 && Board[row][col - 1] == o && Board[row][col - 2] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row, col - 1 });
                completedSOSPositions.push_back({ row, col - 2 });
            }

            // Vertical checks
            if (row <= board_size - 3 && Board[row + 1][col] == o && Board[row + 2][col] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row + 1, col });
                completedSOSPositions.push_back({ row + 2, col });
            }
            if (row >= 2 && Board[row - 1][col] == o && Board[row - 2][col] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row - 1, col });
                completedSOSPositions.push_back({ row - 2, col });
            }

            // Diagonal checks
            if (row <= board_size - 3 && col <= board_size - 3 &&
                Board[row + 1][col + 1] == o && Board[row + 2][col + 2] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row + 1, col + 1 });
                completedSOSPositions.push_back({ row + 2, col + 2 });
            }
            if (row >= 2 && col <= board_size - 3 &&
                Board[row - 1][col + 1] == o && Board[row - 2][col + 2] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row - 1, col + 1 });
                completedSOSPositions.push_back({ row - 2, col + 2 });
            }
            if (row <= board_size - 3 && col >= 2 &&
                Board[row + 1][col - 1] == o && Board[row + 2][col - 2] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row + 1, col - 1 });
                completedSOSPositions.push_back({ row + 2, col - 2 });
            }
            if (row >= 2 && col >= 2 &&
                Board[row - 1][col - 1] == o && Board[row - 2][col - 2] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row - 1, col - 1 });
                completedSOSPositions.push_back({ row - 2, col - 2 });
            }
        }
        // Check if the current cell has an 'O'
        else if (Board[row][col] == o) {
            // Horizontal SOS check
            if (col >= 1 && col <= board_size - 2 && Board[row][col - 1] == s && Board[row][col + 1] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row, col - 1 });
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row, col + 1 });
            }

            // Vertical SOS check
            if (row >= 1 && row <= board_size - 2 && Board[row - 1][col] == s && Board[row + 1][col] == s) {
                sosCount++;
                completedSOSPositions.push_back({ row - 1, col });
                completedSOSPositions.push_back({ row, col });
                completedSOSPositions.push_back({ row + 1, col });
            }

            // Diagonal SOS checks
            if (row >= 1 && row <= board_size - 2 && col >= 1 && col <= board_size - 2) {
                if (Board[row - 1][col - 1] == s && Board[row + 1][col + 1] == s) {
                    sosCount++;
                    completedSOSPositions.push_back({ row - 1, col - 1 });
                    completedSOSPositions.push_back({ row, col });
                    completedSOSPositions.push_back({ row + 1, col + 1 });
                }
                if (Board[row - 1][col + 1] == s && Board[row + 1][col - 1] == s) {
                    sosCount++;
                    completedSOSPositions.push_back({ row - 1, col + 1 });
                    completedSOSPositions.push_back({ row, col });
                    completedSOSPositions.push_back({ row + 1, col - 1 });
                }
            }
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

        // Check if the move forms winning pattern
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

    const std::vector<std::pair<int, int>>& GameLogic::getCompletedSOSPositions() {
        return completedSOSPositions;
    }

    void GameLogic::clearCompletedSOS() {
        completedSOSPositions.clear();
    }

    void GameLogic::SetP1Mode(int mode){
        player1_mode = mode;
    }

    void GameLogic::SetP2Mode(int mode){
        player2_mode = mode;
    }

    int GameLogic::GetP1Mode(){
        return player1_mode;
    }

    int GameLogic::GetP2Mode(){
        return player2_mode;
    }

    bool SimpleGameLogic::IsGameEnded() {
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

    bool GeneralGameLogic::IsGameEnded() {
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

    bool GameLogic::makeMoveComputer() {
        int currplayer = getCurrentPlayer();
        // Iterate through all possible cells on the board
        for (int row = 0; row < board_size; ++row) {
            for (int col = 0; col < board_size; ++col) {
                if (Board[row][col] == "") { // Only check empty cells

                    // Try placing an 'S' and check if it results in SOS
                    Board[row][col] = "S";
                    int s_sosCount = CheckForSOS(row, col);
                    Board[row][col] = "";  // Reset after checking

                    // Try placing an 'O' and check if it results in SOS
                    Board[row][col] = "O";
                    int o_sosCount = CheckForSOS(row, col);
                    Board[row][col] = "";  // Reset after checking

                    // Make the move if it results in an SOS
                    if (s_sosCount > 0 || o_sosCount > 0) {
                        Board[row][col] = (s_sosCount > o_sosCount) ? "S" : "O";
                        if (currplayer == 1){
                            player1Score += s_sosCount;
                            player2Score += o_sosCount;
                        }
                        else if (currplayer == 2){
                            player2Score += s_sosCount;
                            player2Score += o_sosCount;
                        }
                        lastMoveRow = row;  // Track the last move's position in member variables
                        lastMoveCol = col;
                        SetNextPlayer();
                        return true;
                    }
                }
            }
        }

        // If no SOS move, pick any available cell
        for (int row = 0; row < board_size; ++row) {
            for (int col = 0; col < board_size; ++col) {
                if (Board[row][col] == "") {
                    Board[row][col] = (rand() % 2 == 0) ? "S" : "O";
                    lastMoveRow = row;
                    lastMoveCol = col;
                    SetNextPlayer();
                    return true;
                }
            }
        }
        return false;
    }


    int GameLogic::getLastMoveRow() const {
        return lastMoveRow;
    }

    int GameLogic::getLastMoveCol() const {
        return lastMoveCol;
    }

    std::string GameLogic::getComputerLetter() const {
        return Board[lastMoveRow][lastMoveCol];
    }
}
