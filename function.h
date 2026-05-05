#ifndef FUNCTION_H
#define FUNCTION_H

#include <QWidget>
#include "shared.h"
#include "mainwindow.h"

#define MAXSTEP 225 //共225个可能下棋的点

class function : public QWidget
{
    Q_OBJECT

private:
    int historyrow[MAXSTEP]; //上一次落子的行 （最多225次落子）
    int historycol[MAXSTEP]; //上一次落子的列
    Role historyrole[MAXSTEP]; //上一次落子的对象
    bool gameover; //当前是否为最后一步
    int historycount; //记录上一次落子是全局中的第几次

    void recordstep(int row,int col,Role role3);
    void regretstep();

public:
    explicit function(QWidget *parent = nullptr);

private slots:
    void regret(); //悔棋槽函数 方便链接按钮
signals:
};

#endif // FUNCTION_H
