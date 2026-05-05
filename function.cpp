#include "function.h"
#include "shared.h"
#include "chessboard.h"
void function::recordstep(int row, int col, Role role3)
{
    if(historycount>=MAXSTEP)
    {
        return;
    }
    else
    {
        historyrow[historycount]=row; //先给数组赋值后给下标加一
        historycol[historycount]=col;
        historyrole[historycount]=role3;
        historycount++;
    }
}

void function::regretstep()
{
    if(historycount==0) //棋盘已经是空着的了
    {
        return;
    }
    else
    {
        historycount--; //先给下标减一后访问数组的值
        int row=historyrow[historycount];
        int col=historycol[historycount];
        spot[row][col]=EMPTY;
    }
}

function::function(QWidget *parent)
    : QWidget{parent}
{

}
