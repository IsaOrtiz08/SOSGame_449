//game_logic.cpp

#include <iostream>
#include <string>
#include <vector>

namespace SOS {
    class GameLogic {
    private:
        int board_size;
        std::vector<std::vector<std::string>> Board;
        int player1 = 1, player2 = 2;
        int currentPlayer;
        const std::string s = "S";
        const std::string o = "O";
        int player1Score = 0, player2Score = 0;
        int gameMode = 0; //gamemode 0: simple, gamemode 1: general

    public:
        bool GameDone = false;

        void GetBoardSize() {
            int size;
            std::cin >> size;
            std::string error_large_board_size = "Invalid board size. Cannot exceed board larger than 15x15. Please try again";
            std::string error_small_board_size = "Invalid board size. Board must be larger than 2x2. Please try again.";
            if (size > 15) {
                std::cout << error_large_board_size << std::endl;
                GetBoardSize();
            }
            else if (size < 3) {
                std::cout << error_small_board_size << std::endl;
                GetBoardSize();
            }
            else {
                board_size = size;
            }
        }

        std::vector<std::vector<std::string>> CreateBoard() {
            std::vector<std::vector<std::string>> board(board_size, std::vector<std::string>(board_size, ""));
            Board = board;
            return Board;
        }

        bool IsBoardFull() {
            for (int i = 0; i < board_size; i++) {
                for (int j = 0; j < board_size; j++) {
                    if (Board[i][j] == "") {
                        return false;
                    }
                }
            }
            return true;
        }

        void ChooseGameMode(int input) {
            if (input == 0) {
                gameMode = 0;
            }
            else if (input == 1) {
                gameMode = 1;
            }
            else {

            }
        }

        void SetNextPlayer() {
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }

        int CheckForSOS(int row, int col) {
            int sosCount = 0;

            //horizontal check
            if (col >= 1 && col <= board_size - 2 && Board[row][col - 1] == s && Board[row][col - 1] == s && Board[row][col + 1] == s && Board[row][col] == o) {
                sosCount++;
            }

            //vertical check
            if (row >= 1 && row <= board_size - 2 && Board[row - 1][col] == o && Board[row + 1][col] == o && Board[row][col] == o) {
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
        bool makeMove(int row, int col, const std::string& letter) {
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
                if (currentPlayer == 1) {
                    player1Score += sosCount;
                }
                else {
                    player2Score += sosCount;
                }
            }

            // Switch players
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
            return true;
        }

        bool IsGameEnded_Simple() {
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

        bool IsGameEnded_General() {
            std::string playerwins = "You Win!";
            std::string computerwins = "Computer Wins!";
            std::string draw = "Draw!";
            // check if every spot on the board is occupied
            if (!IsBoardFull)
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
}