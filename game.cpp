#include "game.h"
#define OFFX 36
#define OFFY 36
#define JIANGE 56
#define RRRRRR 28
#include<QRect>
#define tong(a1,a2) (a1&16)==(a2&16)
Game::Game(QWidget *parent)
    : QWidget(parent)
{
    // 棋盘初始设置

  const char _board[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0, 20, 19, 18, 17, 16, 17, 18, 19, 20,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0, 21,  0,  0,  0,  0,  0, 21,  0,  0,  0,  0,  0,
      0,  0,  0, 22,  0, 22,  0, 22,  0, 22,  0, 22,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0, 14,  0, 14,  0, 14,  0, 14,  0, 14,  0,  0,  0,  0,
      0,  0,  0,  0, 13,  0,  0,  0,  0,  0, 13,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0, 12, 11, 10,  9,  8,  9, 10, 11, 12,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

// 判断棋子是否在棋盘中的数组
  // 判断棋子是否在棋盘中的数组
   const char _inboard[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
   // 判断棋子是否在九宫的数组
   const char _infort[256] = {
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };


    memcpy(board,_board,256);
    memcpy(inboard,_inboard,256);
    memcpy(infort,_infort,256);
    for(int i=0;i<256;i++)
        gaoliang[i]=false;
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
if(gaoliang[sq])
    painter.drawText(rect,"linght");


}




void Game::chesteps(int sqsrc, QVector<int> &mvs){
    qDebug("create che steps");
   int sqdst=sqsrc;
    for(sqdst++;IN_BOARD(sqdst);sqdst++){
        if(!board[sqdst])
            mvs.append(lMOVE(sqsrc,sqdst));
        else if(tong(board[sqdst],board[sqsrc]))
               break;
        else{mvs.append(lMOVE(sqsrc,sqdst)); break;}
    }
    sqdst=sqsrc;
    for(sqdst--;IN_BOARD(sqdst);sqdst--){
        if(!board[sqdst])
            mvs.append(lMOVE(sqsrc,sqdst));
        else if(tong(board[sqdst],board[sqsrc]))
               break;
        else{mvs.append(lMOVE(sqsrc,sqdst)); break;}
    }

    sqdst=sqsrc;
    for(sqdst+=16;IN_BOARD(sqdst);sqdst+=16){
        if(!board[sqdst])
            mvs.append(lMOVE(sqsrc,sqdst));
        else if(tong(board[sqdst],board[sqsrc]))
               break;
        else{mvs.append(lMOVE(sqsrc,sqdst)); break;}
    }
    sqdst=sqsrc;
    for(sqdst-=16;IN_BOARD(sqdst);sqdst-=16){
        if(!board[sqdst])
            mvs.append(lMOVE(sqsrc,sqdst));
        else if(tong(board[sqdst],board[sqsrc]))
               break;
        else{mvs.append(lMOVE(sqsrc,sqdst)); break;}
    }

}

void Game::paosteps(int sqsrc, QVector<int> &mvs){
    int sqdst=sqsrc;
    int linenum=0;

        for(sqdst++;IN_BOARD(sqdst);sqdst++){
          if(!linenum){
               if(!board[sqdst])
                  mvs.append(lMOVE(sqsrc,sqdst));
                 else
                   linenum++;
          }else{
               if(!board[sqdst])
                   continue;
               else if(tong(board[sqdst],board[sqsrc]))
                      break;
               else{mvs.append(lMOVE(sqsrc,sqdst)); break;}
            }
        }
        sqdst=sqsrc;
        linenum=0;
        for(sqdst--;IN_BOARD(sqdst);sqdst--){
          if(!linenum){
               if(!board[sqdst])
                  mvs.append(lMOVE(sqsrc,sqdst));
                 else
                   linenum++;
          }else{
               if(!board[sqdst])
                   continue;
               else if(tong(board[sqdst],board[sqsrc]))
                      break;
               else{mvs.append(lMOVE(sqsrc,sqdst)); break;}
            }
        }
        sqdst=sqsrc;
        linenum=0;
        for(sqdst+=16;IN_BOARD(sqdst);sqdst+=16){
          if(!linenum){
               if(!board[sqdst])
                  mvs.append(lMOVE(sqsrc,sqdst));
                 else
                   linenum++;
          }else{
               if(!board[sqdst])
                   continue;
               else if(tong(board[sqdst],board[sqsrc]))
                      break;
               else{mvs.append(lMOVE(sqsrc,sqdst)); break;}
            }
        }
        sqdst=sqsrc;
        linenum=0;
        for(sqdst-=16;IN_BOARD(sqdst);sqdst-=16){
          if(!linenum){
               if(!board[sqdst])
                  mvs.append(lMOVE(sqsrc,sqdst));
                 else
                   linenum++;
          }else{
               if(!board[sqdst])
                   continue;
               else if(tong(board[sqdst],board[sqsrc]))
                      break;
               else{mvs.append(lMOVE(sqsrc,sqdst)); break;}
            }
        }


}




bool Game::canmove(int mv){
    qDebug("canmove");
   int sqsrc=lSRC(mv);
   if(board[sqsrc]==0)return false;
   int tmp;
   if(board[sqsrc]<=14)
   {tmp=board[sqsrc]-8;}
   else
      {  tmp=board[sqsrc]-16;}
    QVector <int> mvs;
   switch (tmp) {
   case 0:
       //url+="jiang.png";
       break;
   case 1:
       //url+="shi.png";
       break;
   case 2:
       //url+="xiang.png";
       break;
   case 3:
       //url+="ma.png";
       break;
   case 4:
       chesteps(sqsrc,mvs);
       break;
   case 5:
        paosteps(sqsrc,mvs);
       break;
   case 6:
       //url+="bing.png";
       break;



   default:
       break;
   }

return mvs.contains(mv);
}


void Game::mousePressEvent(QMouseEvent *event){
    int row,col;
    static int  sqsrc=0;
     static int sqdst=0;
    static int sdsrc=0;
    static int sddst=0;
   if(sdsrc==0)
{row=(event->y()-OFFY+JIANGE/2)/JIANGE+3;
   col=(event->x()-OFFX+JIANGE/2)/JIANGE+3;

   sqsrc=lsq(row,col);
    qDebug("%d",sqsrc);
   if(sqsrc<0||sqsrc>255)
       return;
   sdsrc=board[sqsrc];
   qDebug("sdsrc %d",sdsrc);
 if(sdsrc)
     gaoliangon(sqsrc);

}else{
       row=(event->y()-OFFY+JIANGE/2)/JIANGE+3;
          col=(event->x()-OFFX+JIANGE/2)/JIANGE+3;
       sqdst=lsq(row,col);
       qDebug("sqdst %d",sqdst);
       if(sqdst<0||sqdst>255)
           return;
       sddst=board[sqdst];
       if(sddst)
     if(tong(sddst,sdsrc))
     { gaoliangoff(sqsrc);   qDebug("xiangtong"); sqsrc=sqdst;sdsrc=sddst;gaoliangon(sqsrc);update();return;}
     if(canmove(lMOVE(sqsrc,sqdst)))
     {qDebug("haha");
         sdsrc=0;
         gaoliangoff(sqsrc);
         int k=makemove(lMOVE(sqsrc,sqdst));
         //unmove(lMOVE(sqsrc,sqdst),k);
     }
   }


update();
}
int Game::makemove(int mv){
 int src=lSRC(mv);
int dst=lDST(mv);
int killsd=board[dst];
board[dst]=board[src];
board[src]=0;
return killsd;
}
void Game::unmove(int mv, int killsd){
    int src=lSRC(mv);
   int dst=lDST(mv);
   board[src]=board[dst];
   board[dst]=killsd;

}
