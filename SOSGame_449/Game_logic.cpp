//game_logic.cpp

#include <iostream>
#include <string>

namespace SOS {
    class GameLogic {
    private:
        int board_size = 3;
        std::string Board[3][3];
        int player1 = 1, player2 = 2;
        int currentPlayer;
        const std::string s = "S";
        const std::string o = "O";
        int player1Score = 0, player2Score = 0;

    public:
        bool GameDone = false;

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
            if (Board[row][col] != " ") {
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
    };
}