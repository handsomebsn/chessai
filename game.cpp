#include "game.h"
#define OFFX 36
#define OFFY 36
#define JIANGE 56
#define RRRRRR 28
#include<QRect>
#include <QtAlgorithms>
#define tong(id1,id2) (id1&16)==(id2&16)//同一种颜色 只取二进制数的第5位看是否相同
#define butong(id1,id2)  (id1&16)!=(id2&16)
int Game::nHistoryTable[65536];
Game::Game(QWidget *parent)
    : QWidget(parent)
{nDistance=0;
    gameover=false;
    _level=3;
    computerturn=false;
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
  computerscore=0;
  playerscore=0;

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




inline void Game::chesteps(int possrc, QVector<MV> &mvs){
    qDebug("create che steps");
   int posdst=possrc;
    for(posdst++;IN_BOARD(posdst);posdst++){
        if(!board[posdst])//无子
            mvs.append(MV(possrc,posdst));
        else if(tong(board[posdst],board[possrc]))//有子同颜色
               break;
        else{mvs.append(MV(possrc,posdst)); break;}//有子不同色
    }
    posdst=possrc;
    for(posdst--;IN_BOARD(posdst);posdst--){
        if(!board[posdst])
            mvs.append(MV(possrc,posdst));
        else if(tong(board[posdst],board[possrc]))
               break;
        else{mvs.append(MV(possrc,posdst)); break;}
    }

    posdst=possrc;
    for(posdst+=16;IN_BOARD(posdst);posdst+=16){
        if(!board[posdst])
            mvs.append(MV(possrc,posdst));
        else if(tong(board[posdst],board[possrc]))
               break;
        else{mvs.append(MV(possrc,posdst)); break;}
    }
    posdst=possrc;
    for(posdst-=16;IN_BOARD(posdst);posdst-=16){
        if(!board[posdst])
            mvs.append(MV(possrc,posdst));
        else if(tong(board[posdst],board[possrc]))
               break;
        else{mvs.append(MV(possrc,posdst)); break;}
    }

}

inline void Game::paosteps(int possrc, QVector<MV> &mvs){
    int posdst=possrc;
    int linenum=0;

        for(posdst++;IN_BOARD(posdst);posdst++){
          if(!linenum){
               if(!board[posdst])
                  mvs.append(MV(possrc,posdst));
                 else
                   linenum++;
          }else{
               if(!board[posdst])
                   continue;
               else if(tong(board[posdst],board[possrc]))
                      break;
               else{mvs.append(MV(possrc,posdst)); break;}
            }
        }
        posdst=possrc;
        linenum=0;
        for(posdst--;IN_BOARD(posdst);posdst--){
          if(!linenum){
               if(!board[posdst])
                  mvs.append(MV(possrc,posdst));
                 else
                   linenum++;
          }else{
               if(!board[posdst])
                   continue;
               else if(tong(board[posdst],board[possrc]))
                      break;
               else{mvs.append(MV(possrc,posdst)); break;}
            }
        }
        posdst=possrc;
        linenum=0;
        for(posdst+=16;IN_BOARD(posdst);posdst+=16){
          if(!linenum){
               if(!board[posdst])
                  mvs.append(MV(possrc,posdst));
                 else
                   linenum++;
          }else{
               if(!board[posdst])
                   continue;
               else if(tong(board[posdst],board[possrc]))
                      break;
               else{mvs.append(MV(possrc,posdst)); break;}
            }
        }
        posdst=possrc;
        linenum=0;
        for(posdst-=16;IN_BOARD(posdst);posdst-=16){
          if(!linenum){
               if(!board[posdst])
                  mvs.append(MV(possrc,posdst));
                 else
                   linenum++;
          }else{
               if(!board[posdst])
                   continue;
               else if(tong(board[posdst],board[possrc]))
                      break;
               else{mvs.append(MV(possrc,posdst)); break;}
            }
        }


}


inline void Game::bingsteps(int possrc, QVector<MV> &mvs){

   int posdst=possrc;
    if(board[possrc]>=16)
    if(WEI_GUO(possrc,board[possrc]))
    { posdst+=16;
     if(IN_BOARD(posdst))
     if(!board[posdst])
        mvs.append(MV(possrc,posdst));
      else if(butong(board[posdst],board[possrc]))
       mvs.append(MV(possrc,posdst));


    }else{
             posdst+=16;
            if(IN_BOARD(posdst))
            if(!board[posdst])
                mvs.append(MV(possrc,posdst));
              else if(butong(board[posdst],board[possrc]))
               mvs.append(MV(possrc,posdst));
            posdst-=17;
           if(IN_BOARD(posdst))
           if(!board[posdst])
               mvs.append(MV(possrc,posdst));
             else if(butong(board[posdst],board[possrc]))
              mvs.append(MV(possrc,posdst));

           posdst+=2;
          if(IN_BOARD(posdst))
          if(!board[posdst])
              mvs.append(MV(possrc,posdst));
            else if(butong(board[posdst],board[possrc]))
             mvs.append(MV(possrc,posdst));
    }
    else
    if(WEI_GUO(possrc,board[possrc]))
    {
        posdst-=16;
             if(IN_BOARD(posdst))
             if(!board[posdst])
                mvs.append(MV(possrc,posdst));
              else if(butong(board[posdst],board[possrc]))
               mvs.append(MV(possrc,posdst));


     }else{

        posdst-=16;
       if(IN_BOARD(posdst))
       if(!board[posdst])
           mvs.append(MV(possrc,posdst));
         else if(butong(board[posdst],board[possrc]))
          mvs.append(MV(possrc,posdst));
       posdst+=17;
      if(IN_BOARD(posdst))
      if(!board[posdst])
          mvs.append(MV(possrc,posdst));
        else if(butong(board[posdst],board[possrc]))
         mvs.append(MV(possrc,posdst));

      posdst-=2;
     if(IN_BOARD(posdst))
     if(!board[posdst])
         mvs.append(MV(possrc,posdst));
       else if(butong(board[posdst],board[possrc]))
        mvs.append(MV(possrc,posdst));

     }


}

inline void Game::jiangsteps(int possrc, QVector<MV> &mvs){

static const int pianyi[]={-1,1,-16,16};
for(int i=0;i<4;i++)
{
if(IN_FORT(possrc+pianyi[i]))
if(!board[possrc+pianyi[i]])
mvs.append(MV(possrc,possrc+pianyi[i]));
else if(butong(board[possrc+pianyi[i]],board[possrc]))
mvs.append(MV(possrc,possrc+pianyi[i]));
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
          mvs.append(MV(possrc,posdst));

}else{


    for(int posdst=possrc-16;IN_BOARD(posdst);posdst-=16)
           if(!board[posdst])
               continue;
           else if(board[posdst]!=16)
               break;
         else
              mvs.append(MV(possrc,posdst));


}




}


inline void Game::shisteps(int possrc, QVector<MV> &mvs){

    static const int pianyi[]={15,17,-15,-17};
    for(int i=0;i<4;i++)
    {
    if(IN_FORT(possrc+pianyi[i]))
    if(!board[possrc+pianyi[i]])
    mvs.append(MV(possrc,possrc+pianyi[i]));
    else if(butong(board[possrc+pianyi[i]],board[possrc]))
    mvs.append(MV(possrc,possrc+pianyi[i]));
    }


}


inline void Game::xiangsteps(int possrc, QVector<MV> &mvs){

    static const int pianyi[]={30,34,-34,-30};
    static const int xiangyanpanyi[]={15,17,-17,-15};
    for(int i=0;i<4;i++)
    {
    if(IN_BOARD(possrc+pianyi[i])&&WEI_GUO(possrc+pianyi[i],board[possrc])&&!board[possrc+xiangyanpanyi[i]])
    if(!board[possrc+pianyi[i]])
    mvs.append(MV(possrc,possrc+pianyi[i]));
    else if(butong(board[possrc+pianyi[i]],board[possrc]))
    mvs.append(MV(possrc,possrc+pianyi[i]));
    }



}


inline void Game::masteps(int possrc, QVector<MV> &mvs){
    static const int pianyi[4][2] = {{-33, -31}, {-18, 14}, {-14, 18}, {31, 33}};
    static const int mayanpianyi[4]={-16, -1, 1, 16};
    for(int i=0;i<4;i++)
        for(int j=0;j<2;j++)
    {

    if(IN_BOARD(possrc+pianyi[i][j])&&!board[possrc+mayanpianyi[i]])
    if(!board[possrc+pianyi[i][j]])
    mvs.append(MV(possrc,possrc+pianyi[i][j]));
    else if(butong(board[possrc+pianyi[i][j]],board[possrc]))
    mvs.append(MV(possrc,possrc+pianyi[i][j]));
    }


}



bool Game::canmove(MV mv){
    qDebug("canmove");
   int possrc=mv.possrc;
   if(board[possrc]==0)return false;
   int tmp;
   if(board[possrc]<=14)
   {tmp=board[possrc]-8;}
   else
      {  tmp=board[possrc]-16;}
    QVector <MV> mvs;
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
    if(computerturn)
        return;

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
     if(canmove(MV(possrc,posdst)))
     {qDebug("haha");
         sdsrc=0;
         gaoliangoff(possrc);
         makemove1(MV(possrc,posdst));
         //unmove(lMOVE(possrc,posdst),k);
     }
   }


update();
}
int Game::makemove(MV mv){
 int src=mv.possrc;
int dst=mv.posdst;
int killid=board[dst];
int moveid=board[src];
if(killid==8||killid==16)
gameover=true;
if(killid)
DelStone(dst,killid);
DelStone(src,moveid);
AddStone(dst,moveid);
nDistance++;
qDebug("SCORE:%d",score());
return killid;
}
void Game::makemove1(MV mv){
    int src=mv.possrc;
   int dst=mv.posdst;
   int killid=board[dst];
   int moveid=board[src];
   if(killid==8||killid==16)
   gameover=true;
   if(killid)
   DelStone(dst,killid);
   DelStone(src,moveid);
   AddStone(dst,moveid);
   qDebug("move SCORE:%d",score());
   nDistance++;
   if(computerturn)
       computerturn=false;
   else
       computerturn=true;


}
void Game::unmove(MV mv, int killid){
    if(killid==8||killid==16)
    gameover=false;
    int src=mv.possrc;
   int dst=mv.posdst;
   int id=board[dst];
   DelStone(dst,id);
   AddStone(src,id);
   if(killid)
   AddStone(dst,killid);
   nDistance--;
   qDebug("ummove SCORE:%d",score());
}
inline void Game::getAllsteps(QVector<MV> &mvs, bool player){
    int tmp;

    for(int possrc=0;possrc<256;possrc++){
        if(board[possrc]>14&&!player)
            tmp=board[possrc]-16;
        else if(board[possrc]<=14&&board[possrc]>7&&player)
            tmp=board[possrc]-8;
        else
            continue;

qDebug("tmp=%d",tmp);
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


    }
}

int Game::getMinScore(int level, int curMin)
{int killid;
    if(level == 0)
    {
        return score();
    }
    if(gameover)
    return score();
    QVector<MV> steps;
    getAllsteps(steps,true);
    int minInAllMaxScore = 300000;
    for(int i=0;i<steps.count();i++)
    {
        killid=makemove(steps.at(i));
       // qDebug("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww");
        int maxScore = getMaxScore(level - 1, minInAllMaxScore);
        unmove(steps.at(i),killid);
//qDebug("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww");
//qDebug("step:%d",steps.at(i));
        if(maxScore <= curMin)
        {
        qDebug("..............................");
            return maxScore;
        }

        if(maxScore < minInAllMaxScore)
        {
            minInAllMaxScore = maxScore;
        }
    }
    return minInAllMaxScore;
}

int Game::getMaxScore(int level, int curMax)
{int killid;
    if(level == 0)
        return score();
    if(gameover)
    return score();
    QVector<MV> steps;
    getAllsteps(steps,false);
    int maxInAllMinScore = -300000;
    for(int i=0;i<steps.count();i++)
    {
        killid=makemove(steps.at(i));
        int minScore = getMinScore(level - 1, maxInAllMinScore);
        unmove(steps.at(i),killid);
        //qDebug("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");
        if(minScore >= curMax)
        {
            return minScore;
        }
        if(minScore > maxInAllMinScore)
        {
            maxInAllMinScore = minScore;
        }
    }
    return maxInAllMinScore;
}
MV Game::getcomputerbeststep(){
   MV beststep;
   int killid;
   QVector<MV> steps;
    getAllsteps(steps,false);
    //qDebug("gong you %d zou fa",steps.count());
      int maxInAllMinScore = -300000;

      for(int i=0;i<steps.count();i++)
      {
          killid=makemove(steps.at(i));
          int minScore = getMinScore(_level, maxInAllMinScore);
           //qDebug("jumianfenshu %d",minScore);
          unmove(steps.at(i),killid);
          if(minScore > maxInAllMinScore)
          {
              maxInAllMinScore = minScore;
              beststep=steps.at(i);


          }
      }

return beststep;
}

void Game::mouseReleaseEvent(QMouseEvent *event){
if(computerturn){
MV mv=getcomputerbeststep();


makemove1(mv);
update();

}
}
// 超出边界(Fail-Soft)的Alpha-Beta搜索过程
 int Game::SearchFull(int vlAlpha, int vlBeta, int nDepth) {
  int i, nGenMoves, pcCaptured;
  int vl, vlBest;
  MV mvBest(0,0);
  QVector<MV> mvs;
  // 一个Alpha-Beta完全搜索分为以下几个阶段

  // 1. 到达水平线，则返回局面评价值
  if (nDepth == 0) {
    return score();
  }

  // 2. 初始化最佳值和最佳走法
  vlBest = -30000; // 这样可以知道，是否一个走法都没走过(杀棋)
  //mvBest = 0;           // 这样可以知道，是否搜索到了Beta走法或PV走法，以便保存到历史表

  // 3. 生成全部走法，并根据历史表排序
  getAllsteps(mvs);
  nGenMoves=mvs.count();
  //qsort((void*)mvs.begin(), nGenMoves, sizeof(int), CompareHistory);
  qSort(mvs.begin(),mvs.end(), CompareHistory);

  // 4. 逐一走这些走法，并进行递归
  for (i = 0; i < nGenMoves; i ++) {
       pcCaptured= makemove(mvs.at(i));
      vl = -SearchFull(-vlBeta, -vlAlpha, nDepth - 1);
      unmove(mvs.at(i),pcCaptured);

      // 5. 进行Alpha-Beta大小判断和截断
      if (vl > vlBest) {    // 找到最佳值(但不能确定是Alpha、PV还是Beta走法)
        vlBest = vl;        // "vlBest"就是目前要返回的最佳值，可能超出Alpha-Beta边界
        if (vl >= vlBeta) { // 找到一个Beta走法
          mvBest = mvs.at(i);  // Beta走法要保存到历史表
          break;            // Beta截断
        }
        if (vl > vlAlpha) { // 找到一个PV走法
          mvBest = mvs.at(i);  // PV走法要保存到历史表
          vlAlpha = vl;     // 缩小Alpha-Beta边界
        }
      }

  }

  // 5. 所有走法都搜索完了，把最佳走法(不能是Alpha走法)保存到历史表，返回最佳值
  if (vlBest == -30000) {
    // 如果是杀棋，就根据杀棋步数给出评价
    return nDistance - 30000;
  }
  if (mvBest.possrc!=0) {
    // 如果不是Alpha走法，就将最佳走法保存到历史表
    nHistoryTable[lMOVE(mvBest.possrc,mvBest.posdst)] += nDepth * nDepth;
    if (nDistance == 0) {
      // 搜索根节点时，总是有一个最佳走法(因为全窗口搜索不会超出边界)，将这个走法保存下来
      mvResult = mvBest;
    }
  }
  return vlBest;
}
