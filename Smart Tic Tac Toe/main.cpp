#include "ttt.h"

int main(int argc, char *argv[])
{
   TicTacToe game;
   int move,x,xmen,bigO;
   xmen = 0;
   bigO = 0;
   for (x=0; x<argc; x++){

      if(argv[x]&&strcmp(argv[x],"o")==0 || strcmp(argv[x],"O")==0 )
         bigO++;
      else
        if(argv[x]&&strcmp(argv[x],"x")==0 || strcmp(argv[x],"X")==0 )
           xmen++;
   }
   while(!game.gameOver()){
      game.displayBoard();
      printf("Move: ");
      scanf("%d", &move);
      --move;
      if(game.validMove(move)&& xmen != 0){
         game.processMove(move,X_VAL);
         if(!game.gameOver())
           game.OcomputerMove();
      } else {
        printf("invalid move\n");
      }
      if(game.validMove(move) && bigO !=0){
         game.processMove(move,O_VAL);
         if(!game.gameOver())
           game.XcomputerMove();
      } else {
        printf("invalid move\n");
      }
      if(game.validMove(move)&& xmen == 0 && bigO == 0){
         game.processMove(move,X_VAL);
         if(!game.gameOver())
           game.OcomputerMove();
      } else {
        printf("invalid move\n");
      }

   }
   return 0;
}

