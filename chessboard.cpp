#include "chessboard.h"
#include<QPainter>
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
Chessboard::Chessboard(QWidget *parent)
    : QWidget{parent},hoverpaint(false),hoverpointrow(-1),hoverpointcol(-1)
{//初始化列表 给绘制悬停点的判断赋值为0 悬停点的行和列赋值为-1 即让悬停点无效
    for(int i=0;i<chessboardline;i++) //横坐标
    {
        for(int j=0;j<chessboardline;j++) //纵坐标
        {
            spot[i][j]=EMPTY; //初始化棋盘每个点
        }
    }
    //设置鼠标追踪
    setMouseTracking(true);
}
//绘画
void Chessboard::paintEvent(QPaintEvent *event)
{
    //创建画家类
    QPainter painter1(this);
    //去除毛刺（抗锯齿）（可无）
    painter1.setRenderHint(QPainter::Antialiasing);
    //设置背景颜色
    QColor background=QColor(200,180,100);//棋盘颜色为浅棕黄色
    painter1.fillRect(rect(),background);
    //绘制棋盘
    for(int i=0;i<chessboardline;i++)
    {
        //绘制竖线
        painter1.drawLine(margin+i*cellsize,margin,margin+i*cellsize,margin+(chessboardline-1)*cellsize);
        //绘制横线
        painter1.drawLine(margin,margin+i*cellsize,margin+(chessboardline-1)*cellsize,margin+i*cellsize);

    }
    //绘制悬停点
    if(hoverpaint==true&&(hoverpointrow>=0&&hoverpointrow<chessboardline)&&(hoverpointcol>=0&&hoverpointcol<chessboardline)&&spot[hoverpointrow][hoverpointcol]==EMPTY)
    //只写if（hoverpoint&&spot[hoverpointrow][hoverpointcol]==EMPTY）逻辑也成立 因为下方已经判断了悬停点的横纵坐标只能来源于在规定范围内的鼠标移动坐标 rowx coly
    {
        //设置笔刷颜色
        painter1.setBrush(Qt::black);
        //绘制椭圆(Qpoint(center),int rx,int ry)
        //rowx不能直接使用 因为它是鼠标移动的局部变量 但是可以使用hoverpointrow 因为它是在头文件中定义的 且在下面赋值等于rowx的变量
        painter1.drawEllipse(QPoint(margin+hoverpointrow*cellsize,margin+hoverpointcol*cellsize),cellsize/6,cellsize/6);
    }
    //绘制棋子
    for(int i=0;i<chessboardline;i++)
    {
        for(int j=0;j<chessboardline;j++)
        {
            if(spot[i][j]==PLAYER)
            {
                //设置笔刷颜色
                painter1.setBrush(Qt::black);
                painter1.drawEllipse(QPoint(margin+i*cellsize,margin+j*cellsize),cellsize/3,cellsize/3);
            }
            else if(spot[i][j]==COMPUTER)
            {
                painter1.setBrush(Qt::white);
                painter1.drawEllipse(QPoint(margin+i*cellsize,margin+j*cellsize),cellsize/3,cellsize/3);
            }
        }
    }
}
//鼠标移动
void Chessboard::mouseMoveEvent(QMouseEvent *event)
{
    //绝对坐标转换成相对坐标
    int rowx=(event->x()-margin+cellsize/2)/cellsize;
    int coly=(event->y()-margin+cellsize/2)/cellsize;

    if((rowx>=0&&rowx<chessboardline)&&(coly>=0&&coly<chessboardline))
    {
        //保证点的横纵坐标在棋盘范围内
        //原点为零 所以rowx和coly可以取到零
        //此时在鼠标移动事件中 不可能再创建一个绘画事件 只能手动创建绘画事件
        //考虑到鼠标可能有希望下的点附近的无效移动 故只在悬停点坐标改变时触发绘画事件 以节省空间
        if(hoverpointrow!=rowx||hoverpointcol!=coly)
        {
            //赋值
            hoverpointrow=rowx;
            hoverpointcol=coly;
            hoverpaint=true;
            //手动触发更新事件
            update();
        }
    }
    else //不在限定区间内
    {
        hoverpaint=false; //绘制悬停点的判断赋值为0
        hoverpointrow=-1;//鼠标不在限定范围内时 清空原有悬停点
        hoverpointcol=-1;
        update(); //只绘制棋盘不绘制悬停点
    }
}
//鼠标点击
//鼠标点击显示的是绝对坐标 但需要相对坐标
void Chessboard::mousePressEvent(QMouseEvent *event)
{
    int rowx=(event->x()-margin+cellsize/2)/cellsize;
    int coly=(event->y()-margin+cellsize/2)/cellsize;
    //判断鼠标点击是否在棋盘中 即是否鼠标所在位置的相对坐标在规定范围内（即0～14） 且这个点没有棋子
    if((rowx>=0&&rowx<chessboardline)&&(coly>=0&&coly<chessboardline)&&spot[rowx][coly]==EMPTY)
    {
        //插入数据
        spot[rowx][coly]=PLAYER;//只有玩家才可以点击
        //手动更新绘画事件
        update();
        bool playerwin=iswin(rowx,coly,PLAYER);
        if(playerwin==true)
        {
            QMessageBox::information(this,"游戏结束","玩家获胜");
        }
        else
        {
            computermove();
        }
    }
}
bool Chessboard::iswin(int row,int col,Role role) //判断用户或人机是否获胜
{
    //共四条直线八个方向
    int direction[4][2]=
    {                                               //----|---->x
        {1,0},//水平方向                             //    |
        {0,1},//竖直方向                             //    |
        {1,-1},//左上右下                            //    √y
        {1,1} //右上左下
    };
    //遍历
    for(int m=0;m<4;m++)
    {
        int count=1;
        for(int i=1;i<5;i++)
        {
            int nextrow=direction[m][0]*i+row;
            int nextcol=direction[m][1]*i+col;
            if((nextrow<chessboardline&&nextrow>=0)&&(nextcol<chessboardline&&nextcol>=0)&&(spot[nextrow][nextcol]==role))
            {
                count++;
            }
            else
            {
                break;
            }
        }
        for(int j=-1;j>-5;j--)
        {
            int nextrow=direction[m][0]*j+row;
            int nextcol=direction[m][1]*j+col;
            if((nextrow<chessboardline&&nextrow>=0)&&(nextcol<chessboardline&&nextcol>=0)&&(spot[nextrow][nextcol]==role))
            {
                count++;
            }
            else
            {
                break;
            }
        }
        if(count>=5)
        {
            return true;
        }
    }
    return false;
}
int Chessboard::evaluatescore(int row,int col,Role role1)
{
    int sum_score=0; //初始化总分
    //共四条直线八个方向
    int direction[4][2]=
    {                                               //----|---->x
        {1,0},//水平方向                             //    |
        {0,1},//竖直方向                             //    |
        {1,-1},//左上右下                            //    √y
        {1,1} //右上左下
    };
    for(int m=0;m<4;m++) //遍历四个方向
    {
        int count=1; //记录同一直线上相连的同种颜色的棋子的子数（包括当前正在下的点）
        int block=0; //记录同一直线上相连的同种颜色的棋子的相邻共线异色棋子数
        for(int i=1;i<5;i++)
        {
            int nextrow=direction[m][0]*i+row;
            int nextcol=direction[m][1]*i+col;
            Role nextrole=spot[nextrow][nextcol];
            if((nextrow>=0&&nextrow<chessboardline)&&(nextcol>=0&&nextcol<chessboardline))
            {
                if(nextrole==role1)
                {
                    count++;
                }
                else if(nextrole==EMPTY)
                {
                    break;
                }
                else
                {
                    block++;
                    break;
                }
            }
            else
            {
                block++; //边界也算作被堵
                break;
            }
        }
        for(int j=-1;j>-5;j--)
        {
            int nextrow=direction[m][0]*j+row;
            int nextcol=direction[m][1]*j+col;
            Role nextrole=spot[nextrow][nextcol];
            if((nextrow>=0&&nextrow<chessboardline)&&(nextcol>=0&&nextcol<chessboardline))
            {
                if(nextrole==role1)
                {
                    count++;
                }
                else if(nextrole==EMPTY)
                {
                    break;
                }
                else
                {
                    block++;
                    break;
                }
            }
            else
            {
                block++;
                break;
            }
        }
        if(block>2)
        {
            continue;
        }
        if(count>=5)
        {
            sum_score+=WIN;
        }
        else if(count==4)
        {
            if(block==0)
            {
                sum_score+=LIVE_FOUR;
            }
            else if(block==1)
            {
                sum_score+=RUSH_FOUR;
            }
        }
        else if(count==3)
        {
            if(block==0)
            {
                sum_score+=LIVE_THREE;
            }
            else if(block==1)
            {
                sum_score+=SLEEP_THREE;
            }
        }
        else if(count==2)
        {
            if(block==0)
            {
                sum_score+=LIVE_TWO;
            }
            else if(block==1)
            {
                sum_score+=SLEEP_TWO;
            }
        }
    }
    return sum_score;
}
int Chessboard::evaluatesumscore()
{
    int computer_sum_score=0; //初始化玩家和人机的总分
    int player_sum_score=0;
    int difference;
    for(int i=0;i<chessboardline;i++) //遍历棋盘上目前下过棋的所有点
    {
        for(int j=0;j<chessboardline;j++)
        {
            if(spot[i][j]==COMPUTER)
            {
                computer_sum_score+=evaluatescore(i,j,COMPUTER);
            }
            else if(spot[i][j]==PLAYER)
            {
                player_sum_score+=evaluatescore(i,j,PLAYER)*10; //加权 因为黑棋先手 所以人机的防守的优先级应该高于进攻
            }
        }
    }
    difference=computer_sum_score-player_sum_score; //求人机总分数和玩家总分数的差值 来确定人机和玩家在局势上的优劣势差异
    return difference;
}
int Chessboard::alphabeta(int n,int a,int b,bool currentrole)
{
    int maxvalue=-100000;
    int minvalue=100000;
    int value;
    //n为递归层数 a为电脑努力能拿到的最小值 b为玩家努力确保电脑拿到的最大值 currentrole为现在正在进行操作的角色（玩家或者人机）
    if(n==0)
    {
        return evaluatesumscore();
    }
    else
    {
        if(currentrole==true) //现在正在进行操作的角色是人机
        {
            for(int i=0;i<chessboardline;i++) //遍历棋盘上的所有位置
            {
                for(int j=0;j<chessboardline;j++)
                {
                    if(spot[i][j]==EMPTY) //找到其中还没有被下上棋子的空位置
                    {
                        spot[i][j]=COMPUTER; //假设人机在此处落子
                        value=alphabeta(n-1,a,b,false); //通过递归进入下一层 现在进行操作的角色改为玩家
                        spot[i][j]=EMPTY; //假设完毕 回溯
                        maxvalue=qMax(maxvalue,value); //将现有人机能达到的最大值跟假设得到的值做比较 选出其中较大的值作为新的最大值
                        a=qMax(a,value); //alpha作为本层的形参 同时也是下一层的实参 本层由外界传数给alpha 将实数的实参赋给alpha这个形参
                        if(b<=a) //剪枝算法核心 假设玩家足够聪明 人机在本轮里最多只能取到beta 如果其它轮的循环里的人机能保证的最小值大于此时的beta 则说明这一循环是无论如何都不是人机的最优解的 人机可以直接放弃本次循环 转向下一个点 节省运算时间
                        {
                            goto abcutmax;
                        }
                    }
                }
            }
            abcutmax:
                return maxvalue;
        }
        else //现在操作的角色是玩家
        {
            for(int i=0;i<chessboardline;i++) //遍历棋盘上的所有位置
            {
                for(int j=0;j<chessboardline;j++)
                {
                    if(spot[i][j]==EMPTY) //找到其中还没有被下上棋子的空位置
                    {
                        spot[i][j]=PLAYER; //假设玩家在此处落子
                        value=alphabeta(n-1,a,b,true); //通过递归进入下一层 现在进行操作的角色改为玩家
                        spot[i][j]=EMPTY; //假设完毕 回溯
                        minvalue=qMin(minvalue,value); //将现有人机能达到的最大值跟假设得到的值做比较 选出其中较大的值作为新的最大值
                        b=qMin(b,value); //alpha作为本层的形参 同时也是下一层的实参 本层由外界传数给alpha 将实数的实参赋给alpha这个形参
                        if(b<=a) //剪枝算法核心 假设玩家足够聪明 人机在本轮里最多只能取到beta 如果其它轮的循环里的人机能保证的最小值大于此时的beta 则说明这一循环是无论如何都不是人机的最优解的 人机可以直接放弃本次循环 转向下一个点 节省运算时间
                        {
                            goto abcutmin;
                        }
                    }
                }
            }
        }
        abcutmin:
            return minvalue;
    }
}
void Chessboard::computermove() //人机移动
{
    int bestscore=-1000000;
    int bestrow=-1; //初始化人机的行和列
    int bestcol=-1;
    bool has_neighbour[15][15]={false}; //初始化变量
    for(int m=0;m<chessboardline;m++) //遍历所有点
    {
        for(int n=0;n<chessboardline;n++)
        {
            if(spot[m][n]!=EMPTY)
            {
                for(int dm=-2;dm<=2;dm++) //给最近两格的所有点都标为有邻居
                {
                    for(int dn=-2;dn<=2;dn++)
                    {
                        int am=m+dm;
                        int an=n+dn;
                        if(am >= 0 && am < chessboardline && an >= 0 && an < chessboardline)
                        {
                            has_neighbour[am][an]=true;
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<chessboardline;i++) //遍历所有的点
    {
        for(int j=0;j<chessboardline;j++)
        {
            if(spot[i][j]==EMPTY)
            {
                int attack=evaluatescore(i,j,COMPUTER);
                int defense=evaluatescore(i,j,PLAYER);
                if(attack>=WIN)
                {
                    bestrow=i;
                    bestcol=j;
                    goto executemove;
                }
                if(defense>=WIN)
                {
                    bestrow=i;
                    bestcol=j;
                    goto executemove;
                }
                else if(defense>=LIVE_FOUR&&attack<WIN)
                {
                    bestrow = i;
                    bestcol = j;
                    goto executemove;
                }
                else if(defense>=RUSH_FOUR&&attack<WIN)
                {
                    bestrow = i;
                    bestcol = j;
                    goto executemove;
                }
                else if(defense>=LIVE_THREE&&attack<LIVE_FOUR)
                {
                    bestrow = i;
                    bestcol = j;
                    goto executemove;
                }
                if(has_neighbour[i][j]==false)
                {
                    continue;
                }
                spot[i][j]=COMPUTER;
                int currentscore=alphabeta(2,-100000,100000,false);
                spot[i][j]=EMPTY;
                int totalscore;
                totalscore=attack+defense*10+currentscore;
                if(totalscore>bestscore) //如果当前这个点的分数比前面所有点中的最高分还高 就暂定下在这里
                {
                    bestscore=totalscore;
                    bestrow=i;
                    bestcol=j;
                }
            }
        }
    }
    if(bestrow==-1)
    {
        bestscore=-1000000;
        for(int i=0;i<chessboardline;i++)
        {
            for(int j=0;j<chessboardline;j++)
            {
                if(spot[i][j]!=EMPTY)
                {
                    continue;
                }
                int attack=evaluatescore(i,j,COMPUTER);
                int defense=evaluatescore(i,j,PLAYER);
                spot[i][j]=COMPUTER;
                int currentscore=alphabeta(2, -1000000, 1000000, false);
                spot[i][j]=EMPTY;
                int totalscore=attack+defense*3+currentscore;
                if(totalscore>bestscore)
                {
                    bestscore=totalscore;
                    bestrow=i;
                    bestcol=j;
                }
            }
        }
    }
    executemove:

        if((bestrow>=0&&bestrow<chessboardline)&&(bestcol>=0&&bestcol<chessboardline))
        {
            spot[bestrow][bestcol]=COMPUTER; //遍历完所有点后 人机会把棋子下在最优点上
            update(); //更新绘画事件
        }
        bool computerwin=iswin(bestrow,bestcol,COMPUTER);
        if(computerwin==true)
        {
            QMessageBox::information(this,"游戏结束","人机获胜");
        }
}
