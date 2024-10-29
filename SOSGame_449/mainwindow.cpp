#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    connect(ui->startGameButton, &QPushButton::clicked, this, &MainWindow::startGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame() {
    int boardSize = ui->boardsize_input->text().toInt();
    int gameMode = ui->generalgame_button->isChecked() ? 1 : 0;
    if (gameMode == 0){
        gameLogic = new SOS::SimpleGameLogic(boardSize); // Initialize dynamically
    }
    else{
        gameLogic = new SOS::GeneralGameLogic(boardSize);
    }
    ui->currentplayer_label_2->setText(QString::number(gameLogic->getCurrentPlayer()));
    createBoard(boardSize);
    updateScore();

    // Reset button styles
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            buttons[i][j]->setStyleSheet("");  // Reset color and style
        }
    }
    // Start the first turn
    nextTurn();
}



void MainWindow::endGame(SOS::GameLogic* gameLogic){
    QString winner;
    if (gameLogic->getPlayer1Score() > gameLogic->getPlayer2Score()){
        winner = "Player 1 Wins!";
    }
    else {
        winner = "Player 2 Wins!";
    }
    ui->message_label->setText(winner);
}

// creates a board with size x size cells
void MainWindow::createBoard(int size) {
    // Clear old buttons if any
    for (auto& row : buttons) {
        for (auto* btn : row) {
            delete btn;
        }
    }
    buttons.clear();

    // Create new buttons for the game grid
    for (int i = 0; i < size; ++i) {
        std::vector<QPushButton*> row;
        for (int j = 0; j < size; ++j) {
            QPushButton* btn = new QPushButton("");
            row.push_back(btn);
            ui->gridLayout->addWidget(btn, i, j);
            connect(btn, &QPushButton::clicked, [=]() { handleCellClick(i, j); });
        }
        buttons.push_back(row);
    }
}

void MainWindow::nextTurn() {
    if (gameLogic->IsGameEnded() || gameLogic->IsBoardFull()) {
        endGame(gameLogic);
        delete gameLogic;
        gameLogic = nullptr;
        return;
    }

    // Player's turn (either player 1 in general mode or any player in simple mode)
    if (gameLogic->getCurrentPlayer() == 1 || gameLogic->gameMode == 0) {
        return;
    }

    // Computer's turn in general mode
    else if (gameLogic->gameMode == 1 && gameLogic->getCurrentPlayer() == 2) {
        // Computer makes a move
        SOS::GeneralGameLogic* generalLogic = dynamic_cast<SOS::GeneralGameLogic*>(gameLogic);
        if (generalLogic && generalLogic->makeMoveComputer()) {
            // Update the board with the computer's move
            int row = generalLogic->getLastMoveRow();
            int col = generalLogic->getLastMoveCol();
            QString computerLetter = QString::fromStdString(generalLogic->getComputerLetter());

            buttons[row][col]->setText(computerLetter);
            ui->currentplayer_label_2->setText(QString::number(gameLogic->getCurrentPlayer()));

            const auto& sosPositions = gameLogic->getCompletedSOSPositions();
            QString currentPlayerColor = "red";
            for (const auto& pos : sosPositions) {
                int sosRow = pos.first;
                int sosCol = pos.second;

                QString currentStyle = buttons[sosRow][sosCol]->styleSheet();
                if (currentStyle.contains("blue")) {
                    buttons[sosRow][sosCol]->setStyleSheet("color: fuchsia; font-weight: bold;");
                } else {
                    buttons[sosRow][sosCol]->setStyleSheet("color: " + currentPlayerColor + "; font-weight: bold;");
                }
            }

            // Clear SOS positions for the next turn
            gameLogic->clearCompletedSOS();
            updateScore();
            if(gameLogic->IsGameEnded()){
                endGame(gameLogic);
            }
            // check for endgame or start next turn after UI update
            QTimer::singleShot(500, this, &MainWindow::nextTurn);
        }
    }
}


void MainWindow::handleCellClick(int row, int col) {
    QString playerLetter;

    if (gameLogic->getCurrentPlayer() == 1) {
        playerLetter = ui->player1_s_button->isChecked() ? "S" : "O";
    }
    else if (gameLogic->gameMode == 0) {  // Simple mode with player 2
        playerLetter = ui->player2_s_button->isChecked() ? "S" : "O";
    }

    if (gameLogic->makeMove(row, col, playerLetter.toStdString())) {
        buttons[row][col]->setText(playerLetter);
        updateScore();

        const auto& sosPositions = gameLogic->getCompletedSOSPositions();
        QString currentPlayerColor = (gameLogic->getCurrentPlayer() == 1) ? "red" : "blue";
        for(const auto&pos : sosPositions){
            int sosRow = pos.first;
            int sosCol = pos.second;
            QString currentStyle = buttons[sosRow][sosCol]->styleSheet();

            if (!currentStyle.contains(currentPlayerColor) && !currentStyle.isEmpty()) {
                // If already red or blue, set to purple for intersection
                buttons[sosRow][sosCol]->setStyleSheet("color: fuchsia; font-weight: bold;");
            } else {
                // Set to current player's color
                buttons[sosRow][sosCol]->setStyleSheet("color: " + currentPlayerColor + "; font-weight: bold;");
            }
        }
        gameLogic->clearCompletedSOS();
        if(gameLogic->IsGameEnded()){
            endGame(gameLogic);
        }
        ui->currentplayer_label_2->setText(QString::number(gameLogic->getCurrentPlayer()));
        nextTurn();
    } else {
        ui->message_label->setText("This cell is already occupied or move is invalid.");
    }
}



void MainWindow::handlePlayerMove(SOS::GameLogic* gameLogic){
    if (gameLogic->gameMode == 1 && gameLogic->getCurrentPlayer() == 2) { // General mode and computer's turn
        SOS::GeneralGameLogic* generalLogic = dynamic_cast<SOS::GeneralGameLogic*>(gameLogic);
        if (generalLogic->makeMoveComputer()) {
            updateScore();
            ui->currentplayer_label_2->setText(QString::number(gameLogic->getCurrentPlayer()));

            // Check if the game has ended
            if (gameLogic->IsBoardFull() || generalLogic->IsGameEnded()) {
                ui->message_label->setText("Game Over");
            }
        }
    }
}

// show scores on the labels
void MainWindow::updateScore() {
    ui->player1Scorelabel->setText(QString::number(gameLogic->getPlayer1Score()));
    ui->player2Scorelabel->setText(QString::number(gameLogic->getPlayer2Score()));
}
