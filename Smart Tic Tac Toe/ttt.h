
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NOTHING    0
#define X_VAL     -1
#define O_VAL      1

#define NWINS      8
#define BOARDSIZE  9


class TicTacToe {
  private:
    int board[BOARDSIZE];
    int nmoves;
    int winner;
    bool gameover;
    int move,change;
  public:
    TicTacToe();
    ~TicTacToe();
    bool validMove(int move);
    bool gameOver();
    void makemove(int move, int who);
    void unmakeMove(int move, int who);
    void processMove(int move, int who);

    int OcomputerMove();
    int XcomputerMove();
    void displayBoard();
    int boardValue(int who);

    int OcheckcomputerMove();
    int XcheckhumanMove();
    int OOtestcomputerMove();
    int XcheckcomputerMove();
    int OcheckhumanMove();
    int XXtestcomputerMove();

 };

