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
// player子力位置价值表
static const int stonesscores[7][256] = {
  { // 帅(将)
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 1001,  1001, 1001,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 1002,  1002, 1002,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 1001, 1005, 1001,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  }, { // 仕(士)
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 20,  0, 20,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0, 23,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 20,  0, 20,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  }, { // 相(象)
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, 20,  0,  0,  0, 20,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0, 18,  0,  0,  0, 23,  0,  0,  0, 18,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, 20,  0,  0,  0, 20,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  }, { // 马
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0, 90, 90, 90, 96, 90, 96, 90, 90, 90,  0,  0,  0,  0,
    0,  0,  0, 90, 96,103, 97, 94, 97,103, 96, 90,  0,  0,  0,  0,
    0,  0,  0, 92, 98, 99,103, 99,103, 99, 98, 92,  0,  0,  0,  0,
    0,  0,  0, 93,108,100,107,100,107,100,108, 93,  0,  0,  0,  0,
    0,  0,  0, 90,100, 99,103,104,103, 99,100, 90,  0,  0,  0,  0,
    0,  0,  0, 90, 98,101,102,103,102,101, 98, 90,  0,  0,  0,  0,
    0,  0,  0, 92, 94, 98, 95, 98, 95, 98, 94, 92,  0,  0,  0,  0,
    0,  0,  0, 93, 92, 94, 95, 92, 95, 94, 92, 93,  0,  0,  0,  0,
    0,  0,  0, 85, 90, 92, 93, 78, 93, 92, 90, 85,  0,  0,  0,  0,
    0,  0,  0, 88, 85, 90, 88, 90, 88, 90, 85, 88,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  }, { // 车
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,206,208,207,213,214,213,207,208,206,  0,  0,  0,  0,
    0,  0,  0,206,212,209,216,233,216,209,212,206,  0,  0,  0,  0,
    0,  0,  0,206,208,207,214,216,214,207,208,206,  0,  0,  0,  0,
    0,  0,  0,206,213,213,216,216,216,213,213,206,  0,  0,  0,  0,
    0,  0,  0,208,211,211,214,215,214,211,211,208,  0,  0,  0,  0,
    0,  0,  0,208,212,212,214,215,214,212,212,208,  0,  0,  0,  0,
    0,  0,  0,204,209,204,212,214,212,204,209,204,  0,  0,  0,  0,
    0,  0,  0,198,208,204,212,212,212,204,208,198,  0,  0,  0,  0,
    0,  0,  0,200,208,206,212,200,212,206,208,200,  0,  0,  0,  0,
    0,  0,  0,194,206,204,212,200,212,204,206,194,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  }, { // 炮
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,100,100, 96, 91, 90, 91, 96,100,100,  0,  0,  0,  0,
    0,  0,  0, 98, 98, 96, 92, 89, 92, 96, 98, 98,  0,  0,  0,  0,
    0,  0,  0, 97, 97, 96, 91, 92, 91, 96, 97, 97,  0,  0,  0,  0,
    0,  0,  0, 96, 99, 99, 98,100, 98, 99, 99, 96,  0,  0,  0,  0,
    0,  0,  0, 96, 96, 96, 96,100, 96, 96, 96, 96,  0,  0,  0,  0,
    0,  0,  0, 95, 96, 99, 96,100, 96, 99, 96, 95,  0,  0,  0,  0,
    0,  0,  0, 96, 96, 96, 96, 96, 96, 96, 96, 96,  0,  0,  0,  0,
    0,  0,  0, 97, 96,100, 99,101, 99,100, 96, 97,  0,  0,  0,  0,
    0,  0,  0, 96, 97, 98, 98, 98, 98, 98, 97, 96,  0,  0,  0,  0,
    0,  0,  0, 96, 96, 97, 99, 99, 99, 97, 96, 96,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  }, { // 兵(卒)
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  9,  9,  9, 11, 13, 11,  9,  9,  9,  0,  0,  0,  0,
    0,  0,  0, 19, 24, 34, 42, 44, 42, 34, 24, 19,  0,  0,  0,  0,
    0,  0,  0, 19, 24, 32, 37, 37, 37, 32, 24, 19,  0,  0,  0,  0,
    0,  0,  0, 19, 23, 27, 29, 30, 29, 27, 23, 19,  0,  0,  0,  0,
    0,  0,  0, 14, 18, 20, 27, 29, 27, 20, 18, 14,  0,  0,  0,  0,
    0,  0,  0,  7,  0, 13,  0, 16,  0, 13,  0,  7,  0,  0,  0,  0,
    0,  0,  0,  7,  0,  7,  0, 15,  0,  7,  0,  7,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  }
};
class MV{
public:
int possrc;
int posdst;
MV(){}
MV(int _possrc,int _posdst){possrc=_possrc;posdst=_posdst; }
bool operator ==(const MV &mv)const{return possrc==mv.possrc&&posdst==mv.posdst;}
};

class Game : public QWidget
{
    Q_OBJECT
public:
    // 迭代加深搜索过程
     void SearchMain(void) {


         int i, t, vl;

         // 初始化
         memset(nHistoryTable, 0, 65536 * sizeof(int)); // 清空历史表
         t = clock();       // 初始化定时器
        nDistance = 0; // 初始步数

         // 迭代加深过程

         for (i = 0; i <= 30; i ++) {
           vl = SearchFull(-30000, 30000, i);
           // 搜索到杀棋，就终止搜索
           if (vl > 29000 || vl < -29000) {
             break;
           }
           // 超过一秒，就终止搜索
           if (clock() - t > CLOCKS_PER_SEC) {
             break;
           }
         }
     qDebug("depth:%d" ,i);

    }


    static int CompareHistory(const MV &lpmv1, const MV &lpmv2) {
        return 1;
     // return nHistoryTable[ lpmv2] - nHistoryTable[lpmv1];
    }
 private:
    static int nHistoryTable[65536];
    MV mvResult;

private:
    char board[256];//下标pos反映了棋子的位置
    QPainter painter;
    void display(int pos);
    void gaoliangon(int pos){gaoliang[pos]=true;}
    void gaoliangoff(int pos){gaoliang[pos]=false;}
    bool gaoliang[256];
private:
    char inboard[256];
    char infort[256];
    int computerscore;
    int playerscore;
    inline int score(){return computerscore-playerscore;}
    inline void AddStone(int pos, int id) { // 在棋盘上放一枚棋子
        board[pos] = id;
        //加分
        if (id < 16) {
          playerscore += stonesscores[id - 8][pos];
          //zobr.Xor(Zobrist.Table[pc - 8][sq]);
        } else {
          computerscore += stonesscores[id - 16][HUAN_ZHUAN(pos)];
          //zobr.Xor(Zobrist.Table[id - 9][pos]);
        }

      }
    inline void DelStone(int pos,int id){

        board[pos] = 0;
            // 减分
            if (id < 16) {
              playerscore -= stonesscores[id - 8][pos];
              //zobr.Xor(Zobrist.Table[id - 8][pos]);
            } else {
              computerscore -= stonesscores[id - 16][HUAN_ZHUAN(pos)];
             // zobr.Xor(Zobrist.Table[id - 9][pos]);
            }
    }
    inline int getMinScore(int level, int curMin);
    inline int getMaxScore(int level, int curMax);
    MV getcomputerbeststep();
     int SearchFull(int vlAlpha, int vlBeta, int nDepth);
    int _level;
    bool gameover;
    bool computerturn;
    int nDistance;
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
    inline int HUAN_ZHUAN(int pos) {
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
      return (pos & 0x80) == ((id&16) << 3);
    }
    // 是否未过河
    inline bool WEI_GUO(int pos, int id) {
      return (pos & 0x80) != ((id&16) << 3);
    }
    //
    inline void chesteps(int possrc, QVector<MV> &mvs);
    //
    inline void masteps(int possrc,QVector<MV> &mvs);
    //
    inline void paosteps(int possrc,QVector<MV> &mvs);
    //
    inline void bingsteps(int possrc,QVector<MV> &mvs);
    //
    inline void jiangsteps(int possrc,QVector<MV> &mvs);
    //
    inline void shisteps(int possrc,QVector<MV> &mvs);
    //
    inline void xiangsteps(int possrc,QVector<MV> &mvs);
    //
    bool canmove(MV mv);//能否移动
    //a2
    int makemove(MV mv);//移动
    void makemove1(MV mv);
    //
    void unmove(MV mv,int killid);//撤销移动
    ////////////////////////////////////
   inline void getAllsteps(QVector<MV> &mvs,bool player=false);


public slots:
   void paintEvent(QPaintEvent *event);//画图相应函数
   void mousePressEvent(QMouseEvent *event);//鼠标相应函数
  void mouseReleaseEvent(QMouseEvent *event);
};

#endif // GAME_H
