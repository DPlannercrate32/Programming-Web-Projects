
#include "ttt.h"

int wins[NWINS][3]={
  {0,1,2},
  {3,4,5},
  {6,7,8},
  {0,3,6},
  {1,4,7},
  {2,5,8},
  {0,4,8},
  {2,4,6}
};


    TicTacToe::TicTacToe()
    {

     
      int i;

      srandom(getpid());
      gameover = false;
      nmoves = 0;
      winner = NOTHING;
      change = 0;
      for(i=0;i<BOARDSIZE;i++)
        board[i] = NOTHING;
    }
    TicTacToe::~TicTacToe()
    {
      displayBoard();
      if(change == 0){
         switch(winner){
            case NOTHING: printf("cat game\n"); break;
            case  O_VAL: printf("you lose\n"); break;
            case  X_VAL: printf("you win\n") ; break;
         }

       }else{
          switch(winner){
            case NOTHING: printf("cat game\n"); break;
            case  O_VAL: printf("you win\n"); break;
            case  X_VAL: printf("you lose\n") ; break;
         }

       }
      printf("%d\n",winner);
    }
    bool TicTacToe::validMove(int move)
    {
      return (move >=0) && (move <= 8) && (board[move] == 0);
    }
    bool TicTacToe::gameOver()
    {
      return gameover;
    }
    void TicTacToe::makemove(int move, int who)
    {
      nmoves++;
      board[move] = who;
    }


void TicTacToe::unmakeMove(int move, int who)
    {
      --nmoves;
      board[move] = NOTHING;
    }

    void TicTacToe::processMove(int move, int who)
    {
      int i,j,v;
      bool flag;

      board[move] = who;
      for(i=0;i<NWINS;i++){
        flag = true;
        for(j=0;j<3;j++)
          if(board[wins[i][j]] != who){
            flag = false;
            v = boardValue(winner);
            break;
          }
        if(flag){
          gameover = true;
          winner = who;
          return;
        }
      }
      nmoves++;
      if(nmoves == BOARDSIZE)
        gameover = true;
    }


int TicTacToe::OcomputerMove()
    {
      OcheckcomputerMove();
    }
    int TicTacToe::XcomputerMove()
    {
      change++;
      XcheckcomputerMove();
    }
    void TicTacToe::displayBoard()
    {
      int i;

      for(i=0;i<9;i++){
        if(board[i] == NOTHING)
          printf("%d",i+1);
        else
          printf("%c",(board[i] == 1) ? 'O' : 'X');
        printf("%c",((i%3)==2) ? '\n' : '|');
        if((i==2)||(i==5)) printf("-+-+-\n");
      }
    }
    int TicTacToe::boardValue(int who)
    {
     int i,j;
     bool flag;
     for(i=0;i<NWINS;i++){
        flag = true;
        for(j=0;j<3;j++)
          if(board[wins[i][j]] != who){
            flag = false;
            break;
          }

        if(flag)
          return who;
      }
     return NOTHING;
    }

    int TicTacToe::OcheckcomputerMove()
    {
     int i,value,best;
     best = -2;
     for(i = 0; i < 9; i++){

        if(board[i]!= NOTHING)
           continue;
        makemove(i,O_VAL);

        value = boardValue(O_VAL);

        if(value == 0)
            value = XcheckhumanMove();
        unmakeMove(i,O_VAL);
        if(value > best){
           move = i;
           best = value;
           if(best == 1)
              break;
        }
     }
     processMove(move,O_VAL);
    }
    int TicTacToe::XcheckhumanMove()
    {
     int i,value,best;
     best = 2;
     for(i = 0; i < 9; i++){
        if(board[i]!=NOTHING)
           continue;
        makemove(i, X_VAL);
        value = boardValue(X_VAL);

        if(value == 0 && nmoves < BOARDSIZE)
            value = OOtestcomputerMove();

        unmakeMove(i,X_VAL);
        if(value < best){
           best = value;
           if(best == -1)
              return -1;
        }
     }
     return best;
    }

    int TicTacToe::OOtestcomputerMove()
    {
     int i,value,best;
     best = -2;
     for(i = 0; i < 9; i++){

        if(board[i]!= NOTHING)
           continue;
        makemove(i,O_VAL);

        value = boardValue(O_VAL);
        if(value == 0 && nmoves < BOARDSIZE)
            value = XcheckhumanMove();

        unmakeMove(i,O_VAL);
        if(value > best){
           best = value;
           if(best == 1)
              return 1;

        }
     }
     return best;
    }

    int TicTacToe::XcheckcomputerMove()
    {
     int i,value,best;
     best = 2;
     for(i = 0; i < 9; i++){

        if(board[i]!= NOTHING)
           continue;
        makemove(i,X_VAL);

        value = boardValue(X_VAL);

        if(value == 0)
            value = OcheckhumanMove();
        unmakeMove(i,X_VAL);
        if(value < best){
           move = i;
           best = value;
           if(best == -1)
              break;
        }
     }
     processMove(move,X_VAL);
    }

    int TicTacToe::OcheckhumanMove()
    {
     int i,value,best;
     best = -2;
     for(i = 0; i < 9; i++){
        if(board[i]!=NOTHING)
           continue;
        makemove(i, O_VAL);
        value = boardValue(O_VAL);

        if(value == 0 && nmoves < BOARDSIZE)
            value = XXtestcomputerMove();

        unmakeMove(i,O_VAL);
        if(value > best){
           best = value;
           if(best == 1)
              return 1;
        }
     }
     return best;
    }

    int TicTacToe::XXtestcomputerMove()
    {
     int i,value,best;
     best = 2;
     for(i = 0; i < 9; i++){

        if(board[i]!= NOTHING)
           continue;
        makemove(i,X_VAL);

        value = boardValue(X_VAL);
        if(value == 0 && nmoves < BOARDSIZE)
            value = OcheckhumanMove();

        unmakeMove(i,X_VAL);
        if(value < best){
           best = value;
           if(best == -1)
              return -1;

        }
     }
     return best;
    }


 


