#include "game.h"
#define OFFX 36
#define OFFY 36
#define JIANGE 56
#define RRRRRR 28
#include<QRect>
Game::Game(QWidget *parent)
    : QWidget(parent)
{
    memcpy(board,intborad,256);
    setMinimumSize(520,576);
    setMaximumSize(520,576);
}

Game::~Game()
{

}
void Game::paintEvent(QPaintEvent *event){
     painter.begin(this);
     painter.drawImage(0,0,QImage(":/images/BOARD.BMP"));
     for(int sq=0;sq<256;sq++)
         display(sq);
     painter.end();
}

/*A. 0表示空格(没有棋子)；
B. 8~14依次表示player的帅、仕、相、马、车、炮和兵；
C. 16~22依次表示computer的将、士、象、马、车、炮和卒。*/

void Game::display(int sq){
   if(board[sq]==0)
    return;
   int row=lrow(sq)-3;
   int col=lcol(sq)-3;
   QRect rect(col*JIANGE+OFFX-RRRRRR,row*JIANGE+OFFY-RRRRRR,2*RRRRRR,2*RRRRRR);
   int tmp;
   QString url(":/images/");
   if(board[sq]<=14)
   {tmp=board[sq]-8;url+="r";}
   else
      {  tmp=board[sq]-16;url+="b";}
   //qDebug("%d",tmp);
   switch (tmp) {
   case 0:
       url+="jiang.png";
       break;
   case 1:
       url+="shi.png";
       break;
   case 2:
       url+="xiang.png";
       break;
   case 3:
       url+="ma.png";
       break;
   case 4:
       url+="che.png";
       break;
   case 5:
       url+="pao.png";
       break;
   case 6:
       url+="bing.png";
       break;



   default:
       break;
   }



painter.drawImage(rect,QImage(url));



}
