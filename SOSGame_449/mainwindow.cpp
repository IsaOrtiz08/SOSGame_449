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
    int p1_mode = ui->player1_human_button->isChecked() ? 0 : 1;
    int p2_mode = ui->player2_human_button->isChecked() ? 0 : 1;
    if (gameMode == 0){
        gameLogic = new SOS::SimpleGameLogic(boardSize, p1_mode, p2_mode); // Initialize dynamically
    }
    else{
        gameLogic = new SOS::GeneralGameLogic(boardSize, p1_mode, p2_mode);
    }
    ui->currentplayer_label_2->setText(QString::number(gameLogic->getCurrentPlayer()));
    createBoard(boardSize);
    updateScore();
    ui->message_label->setText("");

    // Reset button styles
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            buttons[i][j]->setStyleSheet("");
        }
    }
    // Start the first turn
    nextTurn();
}

void MainWindow::endGame(SOS::GameLogic* gameLogic){
    QString winner;
    if (gameLogic->getPlayer1Score() > gameLogic->getPlayer2Score()){
        winner = "Blue Player Wins!";
    }
    else if (gameLogic->getPlayer2Score() > gameLogic->getPlayer1Score()){
        winner = "Red Player Wins!";
    }
    else{
        winner = "Draw!";
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

    // check for human or computer player's turn
    int currentPlayer = gameLogic->getCurrentPlayer();
    bool isComputerTurn = (currentPlayer == 1 && gameLogic->GetP1Mode() == 1) ||
                          (currentPlayer == 2 && gameLogic->GetP2Mode() == 1);

    // Computer's turn in any game mode
    if (isComputerTurn){
        if (gameLogic->makeMoveComputer()) {
            // Update the board with the computer's move
            int row = gameLogic->getLastMoveRow();
            int col = gameLogic->getLastMoveCol();

            QString computerLetter = QString::fromStdString(gameLogic->getComputerLetter());
            buttons[row][col]->setText(computerLetter);

            ui->currentplayer_label_2->setText(QString::number(gameLogic->getCurrentPlayer()));

            const auto& sosPositions = gameLogic->getCompletedSOSPositions();
            QString currentPlayerColor = (currentPlayer == 1) ? "blue" : "red";
            for (const auto& pos : sosPositions) {
                int sosRow = pos.first;
                int sosCol = pos.second;

                QString currentStyle = buttons[sosRow][sosCol]->styleSheet();
                if (!currentStyle.contains(currentPlayerColor) && !currentStyle.isEmpty()) {
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
                    return;
                }
                // check for endgame or start next turn after UI update
                QTimer::singleShot(700, this, &MainWindow::nextTurn);
            }
    }
    else {
        ui->currentplayer_label_2->setText(QString::number(currentPlayer));
    }
}


void MainWindow::handleCellClick(int row, int col) {
    QString playerLetter;
    int currentPlayer = gameLogic->getCurrentPlayer();
    bool isHumanTurn = (currentPlayer == 1 && gameLogic->GetP1Mode() == 0) ||
                       (currentPlayer == 2 && gameLogic->GetP2Mode() == 0);

    // Only allow human input if it's the human's turn
    if (!isHumanTurn) {
        return;
    }
    if (gameLogic->getCurrentPlayer() == 1) { // check if player 1 is human player
        playerLetter = ui->player1_s_button->isChecked() ? "S" : "O";
    }
    else if (gameLogic->getCurrentPlayer() == 2 ) {  // check if player 2 is human player
        playerLetter = ui->player2_s_button->isChecked() ? "S" : "O";
    }

    if (gameLogic->makeMove(row, col, playerLetter.toStdString())) {
        buttons[row][col]->setText(playerLetter);
        const auto& sosPositions = gameLogic->getCompletedSOSPositions();
        QString currentPlayerColor = (currentPlayer == 1) ? "blue" : "red";
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
        updateScore();

        if(gameLogic->IsGameEnded()){
            endGame(gameLogic);
            return;
        }
        ui->currentplayer_label_2->setText(QString::number(gameLogic->getCurrentPlayer()));
        nextTurn();
    } else {
        ui->message_label->setText("This cell is already occupied or move is invalid.");
    }
}



void MainWindow::handlePlayerMove(SOS::GameLogic* gameLogic){
    bool computer_turn = false;
    // check if this turn is for a computer player
    if (gameLogic->getCurrentPlayer() == 1 && gameLogic->GetP1Mode() == 1){
        computer_turn = true;
    }
    else if (gameLogic->getCurrentPlayer() == 2 && gameLogic->GetP2Mode() == 1){
        computer_turn = true;
    }
    if (computer_turn == true) { // General mode and computer's turn
        if (gameLogic->makeMoveComputer()) {
            updateScore();
            ui->currentplayer_label_2->setText(QString::number(gameLogic->getCurrentPlayer()));
            // Check if the game has ended
            if (gameLogic->IsBoardFull() || gameLogic->IsGameEnded()) {
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
