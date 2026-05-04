#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include"shared.h"
class Chessboard : public QWidget //继承
{
    Q_OBJECT
public:
    explicit Chessboard(QWidget *parent = nullptr);

protected:
    //绘画
    //override用于重写基类函数
    void paintEvent(QPaintEvent *event)override;
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *event)override;
    //鼠标点击
    void mousePressEvent(QMouseEvent *event)override;
    //电脑落子
    void computermove();
private:
    //类的属性 如长宽高等
    static const int chessboardline=15;//棋盘有15根线
    static const int cellsize=40;//棋盘格子大小为40 数据不变用static可以节省内存
    static const int margin=20;//棋盘边缘距离为20
    //用类来确定某个点是否已经有棋子了
    Role spot[chessboardline][chessboardline]; //Role类对象
    //悬停点坐标
    int hoverpointrow;
    int hoverpointcol;
    bool hoverpaint; //用bool类型变量来定义鼠标是否移动到超过设定范围（即棋盘大小） 是否需要绘制悬停点
    bool iswin(int row,int col,Role role); //判断用户是否获胜
    int evaluatescore(int row,int col,Role role1);//评分函数
    int evaluatesumscore();//判断整个局势的优势方
    int alphabeta(int n,int a,int b,bool currentrole);//alphabeta算法 n为递归层数 a为参数alpha b为参数beta
signals:
};

#endif // CHESSBOARD_H
