#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include "game_logic.h"
#include <QString>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleCellClick(int row, int col);
    void startGame();
    void updateScore();
    void endGame(SOS::GameLogic* gameLogic);
    void handlePlayerMove(SOS::GameLogic* gameLogic);
private:
    SOS::GameLogic* gameLogic;
    Ui::MainWindow *ui;
    std::vector<std::vector<QPushButton*>> buttons;
    int boardSize;
    void createBoard(int size);
    void nextTurn();
};
#endif // MAINWINDOW_H
