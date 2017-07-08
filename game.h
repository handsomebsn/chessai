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
    char board[256];
    QPainter painter;
    void display(int sq);
    void gaoliangon(int sq){gaoliang[sq]=true;}
    void gaoliangoff(int sq){gaoliang[sq]=false;}
    bool gaoliang[256];
private:
    char inboard[256];
    char infort[256];

public:
    Game(QWidget *parent = 0);
    ~Game();
    //a1
    // 获得格子的行号
    inline int lrow(int sq) {
      return sq >> 4;//sq/16
    }

    // 获得格子的列号
    inline int lcol(int sq) {
      return sq & 15;//sq%16
    }

    // 根据行号和列号获得格子一维编号sq
    inline int lsq(int row, int col) {
      return col + (row << 4);
    }

    // 翻转格子
    inline int lSQUARE_FLIP(int sq) {
      return 254 - sq;
    }

    // 列号水平镜像
    inline int lmirror_x(int col) {
      return 14 - col;
    }

    // 行号垂直镜像
    inline int lmirror_y(int row) {
      return 15 - row;
    }
    /*
    // 获得红黑标记(红子是8，黑子是16)
    inline int SIDE_TAG(int sd) {
      return 8 + (sd << 3);
    }

    // 获得对方红黑标记
    inline int OPP_SIDE_TAG(int sd) {
      return 16 - (sd << 3);
    }
    */
    // 获得走法的起点
    inline int lSRC(int mv) {
      return mv & 255;//mv%256
    }

    // 获得走法的终点
    inline int lDST(int mv) {
      return mv >> 8;//mv/256
    }

    // 根据起点和终点获得走法
    inline int lMOVE(int sqSrc, int sqDst) {
      return sqSrc + sqDst * 256;
    }

    //a1
     //a2
    // 判断棋子是否在棋盘中
    inline bool IN_BOARD(int sq) {
      return inboard[sq] != 0;
    }
    // 判断棋子是否在九宫中
    inline bool IN_FORT(int sq) {
      return infort[sq] != 0;
    }

    // 是否已过河
    inline bool YI_GUO(int sq, int sd) {
      return (sq & 0x80) == (sd << 7);
    }
    // 是否未过河
    inline bool WEI_GUO(int sq, int sd) {
      return (sq & 0x80) != (sd << 7);
    }
    //
    inline void chesteps(int sqsrc, QVector<int> &mvs);
    //
    inline void masteps(int sqsrc,QVector<int> &mvs);
    //
    inline void paosteps(int sqsrc,QVector<int> &mvs);
    //
    inline void bingsteps(int sqsrc,QVector<int> &mvs);
    //
    inline void jiangsteps(int sqsrc,QVector<int> &mvs);
    //
    inline void shisteps(int sqsrc,QVector<int> &mvs);
    //
    inline void xiangsteps(int sqsrc,QVector<int> &mvs);
    //
    bool canmove(int mv);
    //a2
    int makemove(int mv);
    //
    void unmove(int mv,int killsd);


public slots:
   void paintEvent(QPaintEvent *event);
   void mousePressEvent(QMouseEvent *event);

};

#endif // GAME_H
