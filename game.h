#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include<QPainter>
#include<QVector>
#include<QMouseEvent>
   /*A. 0表示空格(没有棋子)；
　　B. 8~14依次表示player的帅、仕、相、马、车、炮和兵；
　　C. 16~22依次表示computer的将、士、象、马、车、炮和卒。
     长度256的好处将在后面介绍

*/


class Game : public QWidget
{
    Q_OBJECT
private:
    char board[256];//下标pos反映了棋子的位置
    QPainter painter;
    void diposlay(int pos);
    void gaoliangon(int pos){gaoliang[pos]=true;}
    void gaoliangoff(int pos){gaoliang[pos]=false;}
    bool gaoliang[256];
private:
    char inboard[256];
    char infort[256];

public:
    Game(QWidget *parent = 0);
    ~Game();
    //a1
    // 获得格子的行号
    inline int lrow(int pos) {
      return pos >> 4;//pos/16
    }

    // 获得格子的列号
    inline int lcol(int pos) {
      return pos & 15;//pos%16
    }

    // 根据行号和列号获得格子一维编号pos
    inline int lpos(int row, int col) {
      return col + (row << 4);
    }

    // 翻转格子
    inline int lposUARE_FLIP(int pos) {
      return 254 - pos;
    }

    // 列号水平镜像
    inline int lmirror_x(int col) {
      return 14 - col;
    }

    // 行号垂直镜像
    inline int lmirror_y(int row) {
      return 15 - row;
    }
   
    // 获得走法的起点
    inline int lSRC(int mv) {
      return mv & 255;//mv%256
    }

    // 获得走法的终点
    inline int lDST(int mv) {
      return mv >> 8;//mv/256
    }

    // 根据起点和终点获得走法
    inline int lMOVE(int posSrc, int poidst) {
      return posSrc + poidst * 256;
    }

    //a1
     //a2
    // 判断棋子是否在棋盘中
    inline bool IN_BOARD(int pos) {
      return inboard[pos] != 0;
    }
    // 判断棋子是否在九宫中
    inline bool IN_FORT(int pos) {
      return infort[pos] != 0;
    }

    // 是否已过河
    inline bool YI_GUO(int pos, int id) {
      return (pos & 0x80) == (id << 7);
    }
    // 是否未过河
    inline bool WEI_GUO(int pos, int id) {
      return (pos & 0x80) != (id << 7);
    }
    //
    inline void chesteps(int possrc, QVector<int> &mvs);
    //
    inline void masteps(int possrc,QVector<int> &mvs);
    //
    inline void paosteps(int possrc,QVector<int> &mvs);
    //
    inline void bingsteps(int possrc,QVector<int> &mvs);
    //
    inline void jiangsteps(int possrc,QVector<int> &mvs);
    //
    inline void shisteps(int possrc,QVector<int> &mvs);
    //
    inline void xiangsteps(int possrc,QVector<int> &mvs);
    //
    bool canmove(int mv);//能否移动
    //a2
    int makemove(int mv);//移动
    //
    void unmove(int mv,int killid);//撤销移动


public slots:
   void paintEvent(QPaintEvent *event);//画图相应函数
   void mousePressEvent(QMouseEvent *event);//鼠标相应函数

};

#endif // GAME_H
