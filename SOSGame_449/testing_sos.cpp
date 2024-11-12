
#include <QTest>
#include "game_logic.h"

class GameLogicTest : public QObject
{
    Q_OBJECT

private slots:
    // Board Size Tests
    void testBoardSizeLessThanThree();
    void testBoardSizeGreaterThanTwenty();
    void testAcceptableBoardSize();
    void testNullBoardSize();

    // New Game Tests
    void testNewGameSimple();
    void testNewGameGeneral();
    // Simple Game Movement
    void testSimplePlaceS();
    void testSimplePlaceO();
    void testInvalidPlacement();

    // Simple Game Winning Tests
    void testSimpleGameEndP1();
    void testSimpleGameEndP2();

    // General Game Movement
    void testGeneralPlaceS();
    void testGeneralPlaceO();
    void testComputerMove();

    // General Game Winning Test
    void testGeneralGameEnd();

    //Simple Game computer opponent
    void testSimple2Humans();
    void testSimple1Human();
    void testSimple0Humans();

    //General game computer opponent tests
    void testGeneral2Humans();
    void testGeneral1Human();
    void testGeneral0Humans();

};

// board size tests
void GameLogicTest::testBoardSizeLessThanThree()
{
    SOS::SimpleGameLogic gameLogic(2, 0, 0);
    QVERIFY(gameLogic.GameDone);
};

void GameLogicTest::testBoardSizeGreaterThanTwenty()
{
    SOS::SimpleGameLogic gameLogic(21, 0, 0);
    QVERIFY(gameLogic.GameDone);
}

void GameLogicTest::testAcceptableBoardSize()
{
    SOS::SimpleGameLogic gameLogic(10, 0, 0);
    QVERIFY(!gameLogic.GameDone);
}

void GameLogicTest::testNullBoardSize()
{
    SOS::SimpleGameLogic gameLogic(NULL, 0, 0);
    QVERIFY(gameLogic.GameDone);
}

// new game tests
void GameLogicTest::testNewGameSimple()
{
    SOS::SimpleGameLogic gameLogic(4, 0, 0);
    QCOMPARE(gameLogic.gameMode, 0);
}

void GameLogicTest::testNewGameGeneral()
{
    SOS::GeneralGameLogic gameLogic(4, 1, 1);
    QCOMPARE(gameLogic.gameMode, 1);
}

// Simple game movement tests
void GameLogicTest::testSimplePlaceS()
{
    SOS::SimpleGameLogic gameLogic(4, 0, 1);
    gameLogic.makeMove(0, 2, "S");
    QCOMPARE(gameLogic.Board[0][2], QString("S"));
}

void GameLogicTest::testSimplePlaceO()
{
    SOS::SimpleGameLogic gameLogic(4, 0, 1);
    gameLogic.makeMove(0, 2, "O");
    QCOMPARE(gameLogic.Board[0][2], QString("O"));
}

void GameLogicTest::testInvalidPlacement()
{
    SOS::SimpleGameLogic gameLogic(4, 0, 0);
    QVERIFY(!gameLogic.makeMove(0, 6, "S"));
}

//Simple game Winning Tests
void GameLogicTest::testSimpleGameEndP1()
{
    SOS::SimpleGameLogic gameLogic(3, 0, 0);
    gameLogic.makeMove(0, 0, "S"); // player 1 move #1
    gameLogic.makeMove(1, 1, "S"); // player 2 move (not important)
    gameLogic.makeMove(0, 1, "O"); //player 1 move #2
    gameLogic.makeMove(1, 0, "S");
    gameLogic.makeMove(0, 2, "S");// player 1 winning move #3
    QVERIFY(gameLogic.GameDone);
}
void GameLogicTest::testSimpleGameEndP2()
{
    SOS::SimpleGameLogic gameLogic(3, 0, 0);
    gameLogic.makeMove(1, 1, "S"); // player 1 move (not important)
    gameLogic.makeMove(0, 0, "S"); // player 2 move #1
    gameLogic.makeMove(1, 0, "S");
    gameLogic.makeMove(0, 1, "O");// player 2 move #2
    gameLogic.makeMove(1, 2, "S");
    gameLogic.makeMove(0, 2, "S");// player 1 winning move #3
    QVERIFY(gameLogic.GameDone);
}

//General Game Movement tests
void GameLogicTest::testGeneralPlaceS()
{
    SOS::GeneralGameLogic gameLogic(4, 0, 1);
    gameLogic.makeMove(0, 2, "S");
    QVERIFY(gameLogic.Board[0][2] == "S") ;
}

void GameLogicTest::testGeneralPlaceO()
{
    SOS::GeneralGameLogic gameLogic(4, 0, 1);
    gameLogic.makeMove(0, 2, "O");
    QVERIFY(gameLogic.Board[0][2] == "O") ;
}

void GameLogicTest::testComputerMove()
{
    SOS::GeneralGameLogic gameLogic(4, 0, 1);
    gameLogic.SetNextPlayer();
    gameLogic.makeMoveComputer();
    QVERIFY(gameLogic.Board[gameLogic.getLastMoveRow()][gameLogic.getLastMoveCol()] == gameLogic.getComputerLetter());
}

//General game winning test
void GameLogicTest::testGeneralGameEnd()
{
    SOS::GeneralGameLogic gameLogic(3, 0, 0);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameLogic.makeMove(i, j, "S");
        }
    }
    QVERIFY(gameLogic.GameDone);
}

//Simple Game computer opponent
void GameLogicTest::testSimple2Humans()
{
    SOS::SimpleGameLogic gameLogic(3, 0, 0);
    QVERIFY(gameLogic.GetP1Mode() == 0 && gameLogic.GetP2Mode() == 0);
}

void GameLogicTest::testSimple1Human(){
    SOS::SimpleGameLogic gameLogic(3, 1, 0);
    QVERIFY(gameLogic.GetP1Mode() == 1 && gameLogic.GetP2Mode() == 0);
}

void GameLogicTest::testSimple0Humans(){
    SOS::SimpleGameLogic gameLogic(3, 1, 1);
    QVERIFY(gameLogic.GetP1Mode() == 1 && gameLogic.GetP2Mode() == 1);
}

//General game computer opponent tests
void GameLogicTest::testGeneral2Humans()
{
    SOS::GeneralGameLogic gameLogic(3, 0, 0);
    QVERIFY(gameLogic.GetP1Mode() == 0 && gameLogic.GetP2Mode() == 0);
}
void GameLogicTest::testGeneral1Human()
{
    SOS::GeneralGameLogic gameLogic(3, 1, 0);
    QVERIFY(gameLogic.GetP1Mode() == 1 && gameLogic.GetP2Mode() == 0);
}
void GameLogicTest::testGeneral0Humans()
{
    SOS::GeneralGameLogic gameLogic(3, 1, 1);
    QVERIFY(gameLogic.GetP1Mode() == 1 && gameLogic.GetP2Mode() == 1);
}

#ifdef TEST_SOS
QTEST_MAIN(GameLogicTest)
#include "testing_sos.moc"
#endif
