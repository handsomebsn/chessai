#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include<QPainter>
   /*A. 0表示空格(没有棋子)；
　　B. 8~14依次表示player的帅、仕、相、马、车、炮和兵；
　　C. 16~22依次表示computer的将、士、象、马、车、炮和卒。
     长度256的好处将在后面介绍

*/


// 棋盘初始设置

static const char intborad[256] = {
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


class Game : public QWidget
{
    Q_OBJECT
private:
    char board[256];
    QPainter painter;
    void display(int sq);

public:
    Game(QWidget *parent = 0);
    ~Game();
    //day1
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
      return row + (col << 4);
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
      return mv & 255;
    }

    // 获得走法的终点
    inline int lDST(int mv) {
      return mv >> 8;
    }

    // 根据起点和终点获得走法
    inline int lMOVE(int sqSrc, int sqDst) {
      return sqSrc + sqDst * 256;
    }

    //day1



public slots:
   void paintEvent(QPaintEvent *event);


};

#endif // GAME_H
