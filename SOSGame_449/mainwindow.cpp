#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startGameButton, &QPushButton::clicked, this, &MainWindow::startGame);

    // Pass the grid layout from the UI to the function
    //createButtonGrid(ui->gridLayout, boardSize);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame() {
    int boardSize = ui->boardsize_input->text().toInt();
    gameLogic.GetBoardSize(boardSize);
    gameLogic.CreateBoard();
    createBoard(boardSize);
    ui->currentplayer_label_2->setText(QString::number(gameLogic.getCurrentPlayer()));
}

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

void MainWindow::handleCellClick(int row, int col) {
    QString playerLetter;

    // Determine the player's letter based on the radio buttons
    if (gameLogic.getCurrentPlayer() == 1){
        if (ui->player1_s_button->isChecked())
            playerLetter = "S";

        else if (ui->player1_o_button->isChecked())
            playerLetter = "O";
    }
    if (gameLogic.getCurrentPlayer() == 2){
        if (ui->player2_s_button->isChecked())
            playerLetter = "S";

        else if (ui->player2_o_button->isChecked())
            playerLetter = "O";
    }

        std::cout << "Player " << gameLogic.getCurrentPlayer() << " chose: " << playerLetter.toStdString() << std::endl; // for testing purposes

    // make the move on the board if valid
    if (gameLogic.makeMove(row, col, playerLetter.toStdString())) {
        buttons[row][col]->setText(playerLetter);

        updateScore();

        if (gameLogic.IsBoardFull()) {
            ui->message_label->setText("Game Over");
        }
        else {
            ui->currentplayer_label_2->setText(QString::number(gameLogic.getCurrentPlayer()));
        }
    }
    else {
        ui->message_label->setText("This cell is already occupied or move is invalid.");
    }
}


void MainWindow::updateScore() {
    ui->player1Scorelabel->setText(QString::number(gameLogic.getPlayer1Score()));
    ui->player2Scorelabel->setText(QString::number(gameLogic.getPlayer2Score()));
}
