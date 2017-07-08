#include "game.h"
#define OFFX 36
#define OFFY 36
#define JIANGE 56
#define RRRRRR 28
#include<QRect>
#define tong(id1,id2) (id1&16)==(id2&16)//同一种颜色 只取二进制数的第5位看是否相同
#define butong(id1,id2)  (id1&16)!=(id2&16)
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
     for(int pos=0;pos<256;pos++)
         display(pos);
     painter.end();
}

/*A. 0表示空格(没有棋子)；
B. 8~14依次表示player的帅、仕、相、马、车、炮和兵；
C. 16~22依次表示computer的将、士、象、马、车、炮和卒。*/

void Game::display(int pos){
   if(board[pos]==0)
    return;
   int row=lrow(pos)-3;
   int col=lcol(pos)-3;
   QRect rect(col*JIANGE+OFFX-RRRRRR,row*JIANGE+OFFY-RRRRRR,2*RRRRRR,2*RRRRRR);
   int tmp;
   QString url(":/images/");
   if(board[pos]<=14)
   {tmp=board[pos]-8;url+="r";}
   else
      {  tmp=board[pos]-16;url+="b";}
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
if(gaoliang[pos])
    painter.drawText(rect,"linght");


}




void Game::chesteps(int possrc, QVector<int> &mvs){
    qDebug("create che steps");
   int posdst=possrc;
    for(posdst++;IN_BOARD(posdst);posdst++){
        if(!board[posdst])//无子
            mvs.append(lMOVE(possrc,posdst));
        else if(tong(board[posdst],board[possrc]))//有子同颜色
               break;
        else{mvs.append(lMOVE(possrc,posdst)); break;}//有子不同色
    }
    posdst=possrc;
    for(posdst--;IN_BOARD(posdst);posdst--){
        if(!board[posdst])
            mvs.append(lMOVE(possrc,posdst));
        else if(tong(board[posdst],board[possrc]))
               break;
        else{mvs.append(lMOVE(possrc,posdst)); break;}
    }

    posdst=possrc;
    for(posdst+=16;IN_BOARD(posdst);posdst+=16){
        if(!board[posdst])
            mvs.append(lMOVE(possrc,posdst));
        else if(tong(board[posdst],board[possrc]))
               break;
        else{mvs.append(lMOVE(possrc,posdst)); break;}
    }
    posdst=possrc;
    for(posdst-=16;IN_BOARD(posdst);posdst-=16){
        if(!board[posdst])
            mvs.append(lMOVE(possrc,posdst));
        else if(tong(board[posdst],board[possrc]))
               break;
        else{mvs.append(lMOVE(possrc,posdst)); break;}
    }

}

void Game::paosteps(int possrc, QVector<int> &mvs){
    int posdst=possrc;
    int linenum=0;

        for(posdst++;IN_BOARD(posdst);posdst++){
          if(!linenum){
               if(!board[posdst])
                  mvs.append(lMOVE(possrc,posdst));
                 else
                   linenum++;
          }else{
               if(!board[posdst])
                   continue;
               else if(tong(board[posdst],board[possrc]))
                      break;
               else{mvs.append(lMOVE(possrc,posdst)); break;}
            }
        }
        posdst=possrc;
        linenum=0;
        for(posdst--;IN_BOARD(posdst);posdst--){
          if(!linenum){
               if(!board[posdst])
                  mvs.append(lMOVE(possrc,posdst));
                 else
                   linenum++;
          }else{
               if(!board[posdst])
                   continue;
               else if(tong(board[posdst],board[possrc]))
                      break;
               else{mvs.append(lMOVE(possrc,posdst)); break;}
            }
        }
        posdst=possrc;
        linenum=0;
        for(posdst+=16;IN_BOARD(posdst);posdst+=16){
          if(!linenum){
               if(!board[posdst])
                  mvs.append(lMOVE(possrc,posdst));
                 else
                   linenum++;
          }else{
               if(!board[posdst])
                   continue;
               else if(tong(board[posdst],board[possrc]))
                      break;
               else{mvs.append(lMOVE(possrc,posdst)); break;}
            }
        }
        posdst=possrc;
        linenum=0;
        for(posdst-=16;IN_BOARD(posdst);posdst-=16){
          if(!linenum){
               if(!board[posdst])
                  mvs.append(lMOVE(possrc,posdst));
                 else
                   linenum++;
          }else{
               if(!board[posdst])
                   continue;
               else if(tong(board[posdst],board[possrc]))
                      break;
               else{mvs.append(lMOVE(possrc,posdst)); break;}
            }
        }


}


void Game::bingsteps(int possrc, QVector<int> &mvs){

   int posdst=possrc;
    if(board[possrc]>=16)
    if(WEI_GUO(possrc,board[possrc]))
    { posdst+=16;
     if(IN_BOARD(posdst))
     if(!board[posdst])
        mvs.append(lMOVE(possrc,posdst));
      else if(butong(board[posdst],board[possrc]))
       mvs.append(lMOVE(possrc,posdst));

    }else{
             posdst+=16;
            if(IN_BOARD(posdst))
            if(!board[posdst])
                mvs.append(lMOVE(possrc,posdst));
              else if(butong(board[posdst],board[possrc]))
               mvs.append(lMOVE(possrc,posdst));
            posdst-=17;
           if(IN_BOARD(posdst))
           if(!board[posdst])
               mvs.append(lMOVE(possrc,posdst));
             else if(butong(board[posdst],board[possrc]))
              mvs.append(lMOVE(possrc,posdst));

           posdst+=2;
          if(IN_BOARD(posdst))
          if(!board[posdst])
              mvs.append(lMOVE(possrc,posdst));
            else if(butong(board[posdst],board[possrc]))
             mvs.append(lMOVE(possrc,posdst));
    }
    else
    if(WEI_GUO(possrc,board[possrc]))
    {
        posdst-=16;
             if(IN_BOARD(posdst))
             if(!board[posdst])
                mvs.append(lMOVE(possrc,posdst));
              else if(butong(board[posdst],board[possrc]))
               mvs.append(lMOVE(possrc,posdst));


     }else{

        posdst-=16;
       if(IN_BOARD(posdst))
       if(!board[posdst])
           mvs.append(lMOVE(possrc,posdst));
         else if(butong(board[posdst],board[possrc]))
          mvs.append(lMOVE(possrc,posdst));
       posdst+=17;
      if(IN_BOARD(posdst))
      if(!board[posdst])
          mvs.append(lMOVE(possrc,posdst));
        else if(butong(board[posdst],board[possrc]))
         mvs.append(lMOVE(possrc,posdst));

      posdst-=2;
     if(IN_BOARD(posdst))
     if(!board[posdst])
         mvs.append(lMOVE(possrc,posdst));
       else if(butong(board[posdst],board[possrc]))
        mvs.append(lMOVE(possrc,posdst));

     }


}

void Game::jiangsteps(int possrc, QVector<int> &mvs){

static const int pianyi[]={-1,1,-16,16};
for(int i=0;i<4;i++)
{
if(IN_FORT(possrc+pianyi[i]))
if(!board[possrc+pianyi[i]])
mvs.append(lMOVE(possrc,possrc+pianyi[i]));
else if(butong(board[possrc+pianyi[i]],board[possrc]))
mvs.append(lMOVE(possrc,possrc+pianyi[i]));
}
/////////////////////////////////////////////////////
if(board[possrc]>=16)
{
    for(int posdst=possrc+16;IN_BOARD(posdst);posdst+=16)
       if(!board[posdst])
           continue;
       else if(board[posdst]!=8)
           break;
     else
          mvs.append(lMOVE(possrc,posdst));

}else{


    for(int posdst=possrc-16;IN_BOARD(posdst);posdst-=16)
           if(!board[posdst])
               continue;
           else if(board[posdst]!=16)
               break;
         else
              mvs.append(lMOVE(possrc,posdst));


}




}


void Game::shisteps(int possrc, QVector<int> &mvs){

    static const int pianyi[]={15,17,-15,-17};
    for(int i=0;i<4;i++)
    {
    if(IN_FORT(possrc+pianyi[i]))
    if(!board[possrc+pianyi[i]])
    mvs.append(lMOVE(possrc,possrc+pianyi[i]));
    else if(butong(board[possrc+pianyi[i]],board[possrc]))
    mvs.append(lMOVE(possrc,possrc+pianyi[i]));
    }


}


void Game::xiangsteps(int possrc, QVector<int> &mvs){

    static const int pianyi[]={30,34,-34,-30};
    static const int xiangyanpanyi[]={15,17,-17,-15};
    for(int i=0;i<4;i++)
    {
    if(IN_BOARD(possrc+pianyi[i])&&WEI_GUO(possrc+pianyi[i],board[possrc])&&!board[possrc+xiangyanpanyi[i]])
    if(!board[possrc+pianyi[i]])
    mvs.append(lMOVE(possrc,possrc+pianyi[i]));
    else if(butong(board[possrc+pianyi[i]],board[possrc]))
    mvs.append(lMOVE(possrc,possrc+pianyi[i]));
    }



}


void Game::masteps(int possrc, QVector<int> &mvs){
    static const int pianyi[4][2] = {{-33, -31}, {-18, 14}, {-14, 18}, {31, 33}};
    static const int mayanpianyi[4]={-16, -1, 1, 16};
    for(int i=0;i<4;i++)
        for(int j=0;j<2;j++)
    {

    if(IN_BOARD(possrc+pianyi[i][j])&&!board[possrc+mayanpianyi[i]])
    if(!board[possrc+pianyi[i][j]])
    mvs.append(lMOVE(possrc,possrc+pianyi[i][j]));
    else if(butong(board[possrc+pianyi[i][j]],board[possrc]))
    mvs.append(lMOVE(possrc,possrc+pianyi[i][j]));
    }


}



bool Game::canmove(int mv){
    qDebug("canmove");
   int possrc=lSRC(mv);
   if(board[possrc]==0)return false;
   int tmp;
   if(board[possrc]<=14)
   {tmp=board[possrc]-8;}
   else
      {  tmp=board[possrc]-16;}
    QVector <int> mvs;
   switch (tmp) {
   case 0:
        jiangsteps(possrc,mvs);
       break;
   case 1:
       shisteps(possrc,mvs);
       break;
   case 2:
       xiangsteps(possrc,mvs);
       break;
   case 3:
         masteps(possrc,mvs);
       break;
   case 4:
       chesteps(possrc,mvs);
       break;
   case 5:
        paosteps(possrc,mvs);
       break;
   case 6:
       bingsteps(possrc,mvs);
       break;



   default:
       break;
   }

return mvs.contains(mv);
}


void Game::mousePressEvent(QMouseEvent *event){
    int row,col;
    static int  possrc=0;
     static int posdst=0;
    static int sdsrc=0;
    static int sddst=0;
   if(sdsrc==0)
{row=(event->y()-OFFY+JIANGE/2)/JIANGE+3;
   col=(event->x()-OFFX+JIANGE/2)/JIANGE+3;

   possrc=lpos(row,col);
    qDebug("%d",possrc);
   if(possrc<0||possrc>255)
       return;
   sdsrc=board[possrc];
   qDebug("sdsrc %d",sdsrc);
 if(sdsrc)
     gaoliangon(possrc);

}else{
       row=(event->y()-OFFY+JIANGE/2)/JIANGE+3;
          col=(event->x()-OFFX+JIANGE/2)/JIANGE+3;
       posdst=lpos(row,col);
       qDebug("posdst %d",posdst);
       if(posdst<0||posdst>255)
           return;
       sddst=board[posdst];
       if(sddst)
     if(tong(sddst,sdsrc))
     { gaoliangoff(possrc);   qDebug("xiangtong"); possrc=posdst;sdsrc=sddst;gaoliangon(possrc);update();return;}
     if(canmove(lMOVE(possrc,posdst)))
     {qDebug("haha");
         sdsrc=0;
         gaoliangoff(possrc);
         int k=makemove(lMOVE(possrc,posdst));
         //unmove(lMOVE(possrc,posdst),k);
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
