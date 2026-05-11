#include "chessboard.h"
#include<QPainter>
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
#include<cstdlib>
#include <ctime>

Chessboard::Chessboard(QWidget *parent)
    : QWidget{parent},hoverpaint(false),hoverpointrow(-1),hoverpointcol(-1),historycount(0)
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
        if(currentrole==PLAYER)
        {
            //设置笔刷颜色
            painter1.setBrush(Qt::black);
            //绘制椭圆(Qpoint(center),int rx,int ry)
            //rowx不能直接使用 因为它是鼠标移动的局部变量 但是可以使用hoverpointrow 因为它是在头文件中定义的 且在下面赋值等于rowx的变量
            painter1.drawEllipse(QPoint(margin+hoverpointrow*cellsize,margin+hoverpointcol*cellsize),cellsize/6,cellsize/6); //设置悬停点大小
        }
        else if(currentrole==COMPUTER)
        {
            //设置笔刷颜色
            painter1.setBrush(Qt::white);
            //绘制椭圆(Qpoint(center),int rx,int ry)
            //rowx不能直接使用 因为它是鼠标移动的局部变量 但是可以使用hoverpointrow 因为它是在头文件中定义的 且在下面赋值等于rowx的变量
            painter1.drawEllipse(QPoint(margin+hoverpointrow*cellsize,margin+hoverpointcol*cellsize),cellsize/6,cellsize/6); //设置悬停点大小
        }
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
    if((rowx>=0&&rowx<chessboardline)&&(coly>=0&&coly<chessboardline))
    {
        if(click_fly_baseball==true)
        {
            if(spot[rowx][coly]==EMPTY) //技能没有发动成功 不改变现在技能正在发动的状态
            {
                QMessageBox::information(this,"提示","此处没有棋子可以打飞～");
                return;
            }
            else if(spot[rowx][coly]==currentrole) //技能没有发动成功 不改变现在技能正在发动的状态
            {
                QMessageBox::information(this,"提示","啊？打飞自己的棋子吗？");
                return;
            }
            else
            {
                spot[rowx][coly]=EMPTY;
                update();
                QMessageBox::information(this,"这是棒球","技能发动成功，呀嘞呀嘞～");
                click_fly_baseball=false;
                return;
            }
        }
    }

    //判断鼠标点击是否在棋盘中 即是否鼠标所在位置的相对坐标在规定范围内（即0～14） 且这个点没有棋子
    if((rowx>=0&&rowx<chessboardline)&&(coly>=0&&coly<chessboardline)&&spot[rowx][coly]==EMPTY)
    {
        if(gamemode==PVE)
        {
            //插入数据
            spot[rowx][coly]=PLAYER;//只有玩家才可以点击
            //手动更新绘画事件
            update();
            recordstep(rowx,coly,PLAYER);
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
        else
        {
            if(currentrole==PLAYER)
            {
                if(look_PLAYER_history==true)
                {
                    spot[rowx][coly]=PLAYER;
                    update();
                    spot[rowx][coly]=EMPTY;
                    update();
                    QMessageBox::information(this,"提示","看到黑历史，收到精神攻击，出现幻觉，所下的棋子不在原位");
                    look_PLAYER_history=false;
                    static bool first=true;
                    if(first==true)
                    {
                        std::srand(std::time(nullptr));
                        first=false; //确保初始化随机数种子的过程只进行一次
                    }
                    int count=0; //记录数组下标
                    for(int i=0;i<chessboardline;i++)
                    {
                        for(int j=0;j<chessboardline;j++)
                        {
                            if(spot[i][j]==EMPTY)
                            {
                                lookrow[count]=i;
                                lookcol[count]=j;
                                count++;
                            }
                        }
                    }
                    int number=std::rand()%count;
                    rowx=lookrow[number];
                    coly=lookcol[number];
                    spot[rowx][coly]=PLAYER;
                    update();
                }
                spot[rowx][coly]=PLAYER;
                update();
                recordstep(rowx,coly,PLAYER);
                bool player1win=iswin(rowx,coly,PLAYER);
                if(player1win==true)
                {
                    QMessageBox::information(this,"游戏结束","黑棋胜利");
                }
                else if (isboardfull())
                {
                    draw();
                    return;
                }
                else
                {
                    if(keepcurrentrole==true)
                    {
                        currentrole=PLAYER;
                        keepcurrentrole=false;
                    }
                    else
                    {
                        currentrole=COMPUTER;
                    }

                }
            }
            else if(currentrole==COMPUTER)
            {
                if(look_COMPUTER_history==true)
                {
                    spot[rowx][coly]=COMPUTER;
                    update();
                    spot[rowx][coly]=EMPTY;
                    update();
                    QMessageBox::information(this,"提示","看到黑历史，收到精神攻击，出现幻觉，所下的棋子不在原位");
                    look_COMPUTER_history=false;
                    static bool first=true;
                    if(first==true)
                    {
                        std::srand(std::time(nullptr));
                        first=false; //确保初始化随机数种子的过程只进行一次
                    }
                    int count=0; //记录数组下标
                    for(int i=0;i<chessboardline;i++)
                    {
                        for(int j=0;j<chessboardline;j++)
                        {
                            if(spot[i][j]==EMPTY)
                            {
                                lookrow[count]=i;
                                lookcol[count]=j;
                                count++;
                            }
                        }
                    }
                    int number=std::rand()%count;
                    rowx=lookrow[number];
                    coly=lookcol[number];
                    spot[rowx][coly]=COMPUTER;
                    update();
                }
                spot[rowx][coly]=COMPUTER;
                update();
                recordstep(rowx,coly,COMPUTER);
                bool player2win=iswin(rowx,coly,COMPUTER);
                if(player2win==true)
                {
                    QMessageBox::information(this,"游戏结束","白棋胜利");
                }
                else if (isboardfull())
                {
                    draw();
                    return;
                }
                else
                {
                    if(keepcurrentrole==true)
                    {
                        currentrole=COMPUTER;
                        keepcurrentrole=false;
                    }
                    else
                    {
                        currentrole=PLAYER;
                    }
                }
            }
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
        if(block>=2)
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
    int bestrow = -1;
    int bestcol = -1;
    int bestscore = -1000000;
    bool move_decided = false; // 用于标记是否已确定落子

    // 存储关键威胁点，最大不超过棋盘上空格总数 225
    QPoint player_threats[225];
    int player_count = 0;
    QPoint ai_threats[225];
    int ai_count = 0;

    // 扫描棋盘找威胁
    for(int i = 0; i < chessboardline; i++)
    {
        for(int j = 0; j < chessboardline; j++)
        {
            if(spot[i][j] == EMPTY)
            {
                int player_score = evaluatescore(i, j, PLAYER);
                int ai_score = evaluatescore(i, j, COMPUTER);

                // 玩家威胁点收集
                if(player_score >= WIN || player_score >= LIVE_FOUR || player_score >= RUSH_FOUR || player_score >= LIVE_THREE)
                {
                    player_threats[player_count].setX(i);
                    player_threats[player_count].setY(j);
                    player_count++;
                }

                // AI 自己关键点收集
                if(ai_score >= WIN || ai_score >= LIVE_FOUR)
                {
                    ai_threats[ai_count].setX(i);
                    ai_threats[ai_count].setY(j);
                    ai_count++;
                }
            }
        }
    }

    // 1. AI 连五 → 立即落子
    for(int idx = 0; idx < ai_count; idx++)
    {
        int x = ai_threats[idx].x();
        int y = ai_threats[idx].y();
        if(evaluatescore(x, y, COMPUTER) >= WIN)
        {
            bestrow = x;
            bestcol = y;
            move_decided = true;
            break;
        }
    }

    // 2. 玩家连五 → 必须堵
    if(!move_decided)
    {
        for(int idx = 0; idx < player_count; idx++)
        {
            int x = player_threats[idx].x();
            int y = player_threats[idx].y();
            if(evaluatescore(x, y, PLAYER) >= WIN)
            {
                bestrow = x;
                bestcol = y;
                move_decided = true;
                break;
            }
        }
    }

    // 3. 玩家活四 → 必须堵
    if(!move_decided)
    {
        for(int idx = 0; idx < player_count; idx++)
        {
            int x = player_threats[idx].x();
            int y = player_threats[idx].y();
            int score = evaluatescore(x, y, PLAYER);
            if(score >= LIVE_FOUR || score >= RUSH_FOUR)
            {
                bestrow = x;
                bestcol = y;
                move_decided = true;
                break;
            }
        }
    }

    // 4. 玩家双活三 → 优先堵
    if(!move_decided)
    {
        int max_threat = -1;
        for(int idx = 0; idx < player_count; idx++)
        {
            int x = player_threats[idx].x();
            int y = player_threats[idx].y();
            int score = evaluatescore(x, y, PLAYER);
            if(score >= LIVE_THREE && score > max_threat)
            {
                max_threat = score;
                bestrow = x;
                bestcol = y;
            }
        }
        if(max_threat > 0)
            move_decided = true;
    }

    // 5. AI 活四/活三 → 进攻
    if(!move_decided)
    {
        int max_attack = -1;
        for(int idx = 0; idx < ai_count; idx++)
        {
            int x = ai_threats[idx].x();
            int y = ai_threats[idx].y();
            int score = evaluatescore(x, y, COMPUTER);
            if(score >= LIVE_FOUR || score >= LIVE_THREE)
            {
                if(score > max_attack)
                {
                    max_attack = score;
                    bestrow = x;
                    bestcol = y;
                }
            }
        }
        if(max_attack > 0)
            move_decided = true;
    }

    // 6. 没有紧急威胁 → 普通评分选择最优点
    if(!move_decided)
    {
        bool has_neighbour[15][15] = {false};
        for(int m = 0; m < chessboardline; m++)
        {
            for(int n = 0; n < chessboardline; n++)
            {
                if(spot[m][n] != EMPTY)
                {
                    for(int dm = -2; dm <= 2; dm++)
                        for(int dn = -2; dn <= 2; dn++)
                        {
                            int am = m + dm;
                            int an = n + dn;
                            if(am >= 0 && am < chessboardline && an >= 0 && an < chessboardline)
                                has_neighbour[am][an] = true;
                        }
                }
            }
        }

        for(int i = 0; i < chessboardline; i++)
        {
            for(int j = 0; j < chessboardline; j++)
            {
                if(spot[i][j] == EMPTY && has_neighbour[i][j])
                {
                    spot[i][j] = COMPUTER;
                    int currentscore = alphabeta(2, -100000, 100000, false);
                    spot[i][j] = EMPTY;
                    int attack = evaluatescore(i, j, COMPUTER);
                    int defense = evaluatescore(i, j, PLAYER);
                    int totalscore = attack * 2 + defense * 5 + currentscore;
                    if(totalscore > bestscore)
                    {
                        bestscore = totalscore;
                        bestrow = i;
                        bestcol = j;
                    }
                }
            }
        }
    }

    // 最终落子
    if(bestrow >= 0 && bestcol >= 0)
    {
        spot[bestrow][bestcol] = COMPUTER;
        update();
        recordstep(bestrow,bestcol,COMPUTER);
    }

    if(iswin(bestrow, bestcol, COMPUTER))
    {
        QMessageBox::information(this, "游戏结束", "人机获胜");
    }
}
void Chessboard::setgamemode(Gamemode mode)
{
    gamemode = mode;
}


void Chessboard::recordstep(int row, int col, Role role3)
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

void Chessboard::regretstep()
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

bool Chessboard::can_use_skill()
{
    if(cannot_use_skill==true)
    {
        cannot_use_skill=false;
        QMessageBox::information(this,"提示","对手发动了擒拿擒拿技能，本局玩家不可再发动技能");
        return false;
    }
    else
    {
        return true;
    }
}

void Chessboard::regret()
{
    if(gamemode==PVE)
    {
        if(historycount<2)
        {
            QMessageBox::information(this,"提示","步数不足，无法悔棋");
            return;
        }
        else
        {
            regretstep(); //撤回人机的一步
            regretstep(); //撤回玩家的一步
        }
    }
    else
    {
        if(historycount<1)
        {
            QMessageBox::information(this,"提示","步数不足，无法悔棋");
            return;
        }
        else
        {
            Role temprole=historyrole[historycount-1]; //用临时角色变量记录悔棋这步的动作发出者 方便后续重新从这个玩家开始继续游戏
            regretstep(); //悔棋 此时这一步的全部变量都被清除
            currentrole=temprole;
        }
    }
    update();
}

void Chessboard::draw()
{
    QMessageBox::information(this,"提示","对局结束，双方平局");
}

void Chessboard::fly_sand_go_stone() //随即移走对方的一颗棋子 一局只能发动一次
{
    if(can_use_skill()==false)
    {
        return;
    }
    Role opponentrole=(currentrole==PLAYER?COMPUTER:PLAYER); //不应将opponentrole的定义和初始化写在头文件里 否则只初始化一次 只能删一个角色的棋子 应写在函数中 每次调用函数时根据当前角色对opponent进行动态初始化
    static bool first=true;
    bool skill_fly_canuse=false;

    if(currentrole==PLAYER)
    {
        skill_fly_canuse=!skill_fly_PLAYER_used;
    }
    else if(currentrole==COMPUTER)
    {
        skill_fly_canuse=!skill_fly_COMPUTER_used;
    }

    if(first==true)
    {
        std::srand(std::time(nullptr));
        first=false; //确保初始化随机数种子的过程只进行一次
    }

    if((currentrole!=PLAYER)&&(currentrole!=COMPUTER)) //这段代码可以没有 只是为了补全逻辑
    {
        QMessageBox::information(this,"提示","未开局，不能使用技能");
        return;
    }
    else
    {
        if(skill_fly_canuse==false)
        {

            QMessageBox::information(this,"提示","本轮飞沙走石技能已经使用过，技能发动失败");
            return;

        }
        else
        {
            int count=0; //初始化对手落子的数组下标
            for(int i=0;i<chessboardline;i++)
            {
                for(int j=0;j<chessboardline;j++)
                {
                    if(spot[i][j]==opponentrole)
                    {
                        opponentrow[count]=i;
                        opponentcol[count]=j;
                        count++;
                    }
                }
            }
            if(count==0)
            {
                QMessageBox::information(this,"提示","对方棋盘上没有棋子，技能发动失败");
                return;
            }
            int number=std::rand()%count; //生成随机数 对count取模 保证最后产生的数组下标小于对方现有的棋子数对应的count
            int temprow=opponentrow[number];
            int tempcol=opponentcol[number];
            spot[temprow][tempcol]=EMPTY; //清除生成的随机位置上的对手的棋子
            QMessageBox::information(this,"飞沙走石","技能发动成功，什刹海见！");
            if (currentrole==PLAYER) //标记本轮技能已经使用
            {
                skill_fly_PLAYER_used=true;
            }
            else if(currentrole==COMPUTER)
            {
                skill_fly_COMPUTER_used=true;
            }
        }
    }
}

void Chessboard::strength_uproot_mountain() //掀翻整个棋盘 即清空棋盘上的所有棋子 一局只能发动一次
{
    if(can_use_skill()==false)
    {
        return;
    }
    bool skill_strength_canuse=false;
    if(currentrole==PLAYER)
    {
        skill_strength_canuse=!skill_strength_PLAYER_used;
    }
    else if(currentrole==COMPUTER)
    {
        skill_strength_canuse=!skill_strength_COMPUTER_used;
    }
    if((currentrole!=PLAYER)&&(currentrole!=COMPUTER)) //这段代码可以没有 只是为了补全逻辑
    {
        QMessageBox::information(this,"提示","未开局，不能使用技能");
        return;
    }
    else
    {
        if(skill_strength_canuse==false)
        {

            QMessageBox::information(this,"提示","本轮力拔山兮技能已经使用过，技能发动失败");
            return;
        }
        else
        {
            for(int i=0;i<chessboardline;i++)
            {
                for(int j=0;j<chessboardline;j++)
                {
                    spot[i][j]=EMPTY; //清空棋盘
                    update();
                }
            }
            QMessageBox::information(this,"力拔山兮","技能发动成功，摔坏棋盘，离获胜更进一步！");
            if (currentrole==PLAYER) //标记本轮技能已经使用
            {
                skill_strength_PLAYER_used=true;
            }
            else if(currentrole==COMPUTER)
            {
                skill_strength_COMPUTER_used=true;
            }
        }
    }
}

void Chessboard::still_like_stagnant_water() //暂停对方一回合 即己方可以连续下两回合棋 一局只能发动一次
{
    if(can_use_skill()==false)
    {
        return;
    }
    bool skill_still_canuse=false;
    if(currentrole==PLAYER)
    {
        skill_still_canuse=!skill_still_PLAYER_used;
    }
    else if(currentrole==COMPUTER)
    {
        skill_still_canuse=!skill_still_COMPUTER_used;
    }
    if((currentrole!=PLAYER)&&(currentrole!=COMPUTER)) //这段代码可以没有 只是为了补全逻辑
    {
        QMessageBox::information(this,"提示","未开局，不能使用技能");
        return;
    }
    else
    {
        if(skill_still_canuse==false)
        {

            QMessageBox::information(this,"提示","本轮静如止水技能已经使用过，技能发动失败");
            return;
        }
        else
        {
            keepcurrentrole=true;
            QMessageBox::information(this,"静如止水","技能发动成功，凝结时间，冻结空气，对手已经完全动不了了！");
            if (currentrole==PLAYER) //标记本轮技能已经使用
            {
                skill_still_PLAYER_used=true;
            }
            else if(currentrole==COMPUTER)
            {
                skill_still_COMPUTER_used=true;
            }
        }
    }
}

void Chessboard::this_is_baseball() //打飞对方的一颗棋子 可以用鼠标指定 一局只能发动一次
{
    if(can_use_skill()==false)
    {
        return;
    }
    bool skill_baseball_canuse=false;
    if(currentrole==PLAYER)
    {
        skill_baseball_canuse=!skill_baseball_PLAYER_used;
    }
    else if(currentrole==COMPUTER)
    {
        skill_baseball_canuse=!skill_baseball_COMPUTER_used;
    }
    if((currentrole!=PLAYER)&&(currentrole!=COMPUTER)) //这段代码可以没有 只是为了补全逻辑
    {
        QMessageBox::information(this,"提示","未开局，不能使用技能");
        return;
    }
    else
    {
        if(skill_baseball_canuse==false)
        {

            QMessageBox::information(this,"提示","本轮这是棒球技能已经使用过，技能发动失败");
            return;
        }
        else
        {
            click_fly_baseball=true;
            QMessageBox::information(this,"技能发动成功","这叫棒球！");
            if (currentrole==PLAYER) //标记本轮技能已经使用
            {
                skill_baseball_PLAYER_used=true;
            }
            else if(currentrole==COMPUTER)
            {
                skill_baseball_COMPUTER_used=true;
            }
        }
    }
}

void Chessboard::i_am_cleaning()
{
    if(can_use_skill()==false)
    {
        return;
    }
    Role opponentrole=(currentrole==PLAYER?COMPUTER:PLAYER);
    static bool first=true;
    bool skill_cleaning_canuse=false;

    if(first==true)
    {
        std::srand(std::time(nullptr));
        first=false; //确保初始化随机数种子的过程只进行一次
    }

    if(currentrole==PLAYER)
    {
        skill_cleaning_canuse=!skill_cleaning_PLAYER_used;
    }
    else if(currentrole==COMPUTER)
    {
        skill_cleaning_canuse=!skill_cleaning_COMPUTER_used;
    }

    if((currentrole!=PLAYER)&&(currentrole!=COMPUTER)) //这段代码可以没有 只是为了补全逻辑
    {
        QMessageBox::information(this,"提示","未开局，不能使用技能");
        return;
    }
    else
    {
        if(skill_cleaning_canuse==false)
        {

            QMessageBox::information(this,"提示","本轮我是保洁技能已经使用过，技能发动失败");
            return;
        }
        else
        {
            int count=0;
            for(int i=0;i<chessboardline;i++)
            {
                for(int j=0;j<chessboardline;j++)
                {
                    if(spot[i][j]==opponentrole)
                    {
                        cleaningrow[count]=i;
                        cleaningcol[count]=j;
                        count++;
                    }
                }
            }
            if(count==0)
            {
                QMessageBox::information(this,"提示","对方棋盘上没有棋子，技能发动失败");
                return;
            }
            int rounds=std::rand()%3+1; //随机生成一个1～3之间的数字
            for(int k=0;k<rounds;k++)
            {
                int number=std::rand()%count;
                int temprow=cleaningrow[number];
                int tempcol=cleaningcol[number];
                spot[temprow][tempcol]=EMPTY;
                update();
                count--;
                cleaningrow[number]=cleaningrow[count]; //用此时数组的最后一个行数和列数代替被删除的棋子的位置 防止删除完棋子之后再随机到这个位置没有棋子可删
                cleaningcol[number]=cleaningcol[count];
            }
            QMessageBox::information(this,"技能发动成功","窝是包接");
            if (currentrole==PLAYER) //标记本轮技能已经使用
            {
                skill_cleaning_PLAYER_used=true;
            }
            else if(currentrole==COMPUTER)
            {
                skill_cleaning_COMPUTER_used=true;
            }
        }
    }
}

void Chessboard::seize_hold()
{
    if(can_use_skill()==false)
    {
        return;
    }
    bool skill_seize_canuse=false;
    if(currentrole==PLAYER)
    {
        skill_seize_canuse=!skill_seize_PLAYER_used;
    }
    else if(currentrole==COMPUTER)
    {
        skill_seize_canuse=!skill_seize_COMPUTER_used;
    }
    if((currentrole!=PLAYER)&&(currentrole!=COMPUTER)) //这段代码可以没有 只是为了补全逻辑
    {
        QMessageBox::information(this,"提示","未开局，不能使用技能");
        return;
    }
    else
    {
        if(skill_seize_canuse==false)
        {

            QMessageBox::information(this,"提示","本轮擒拿擒拿技能已经使用过，技能发动失败");
            return;
        }
        else
        {
            cannot_use_skill=true;
            QMessageBox::information(this,"技能发动成功","擒住天地之精华，拿得老师笑哈哈");
            if (currentrole==PLAYER) //标记本轮技能已经使用
            {
                skill_seize_PLAYER_used=true;
            }
            else if(currentrole==COMPUTER)
            {
                skill_seize_COMPUTER_used=true;
            }
        }
    }
}

void Chessboard::find_gold_no_hide() //在棋盘上的随机空位出现一颗自己的棋子
{
    if(can_use_skill()==false)
    {
        return;
    }
    static bool first=true;
    bool skill_find_canuse=false;

    if(first==true)
    {
        std::srand(std::time(nullptr));
        first=false; //确保初始化随机数种子的过程只进行一次
    }

    if(currentrole==PLAYER)
    {
        skill_find_canuse=!skill_find_PLAYER_used;
    }
    else if(currentrole==COMPUTER)
    {
        skill_find_canuse=!skill_find_COMPUTER_used;
    }

    if((currentrole!=PLAYER)&&(currentrole!=COMPUTER)) //这段代码可以没有 只是为了补全逻辑
    {
        QMessageBox::information(this,"提示","未开局，不能使用技能");
        return;
    }
    else
    {
        if(skill_find_canuse==false)
        {

            QMessageBox::information(this,"提示","本轮拾金不昧技能已经使用过，技能发动失败");
            return;
        }
        else
        {
            int count=0; //记录数组下标
            for(int i=0;i<chessboardline;i++)
            {
                for(int j=0;j<chessboardline;j++)
                {
                    if(spot[i][j]==EMPTY)
                    {
                        emptyrow[count]=i;
                        emptycol[count]=j;
                        count++;
                    }
                }
            }
            int number=std::rand()%count;
            int temprow=emptyrow[number];
            int tempcol=emptycol[number];
            if(currentrole==PLAYER)
            {
                spot[temprow][tempcol]=PLAYER;
            }
            else if(currentrole==COMPUTER)
            {
                spot[temprow][tempcol]=COMPUTER;
            }
            QMessageBox::information(this,"技能发动成功","你掉的是什刹海里的五子棋，还是羊汤里的五子棋呢？");
            if (currentrole==PLAYER) //标记本轮技能已经使用
            {
                skill_find_PLAYER_used=true;
            }
            else if(currentrole==COMPUTER)
            {
                skill_find_COMPUTER_used=true;
            }
        }
    }
}

void Chessboard::look_at_embarrassing_history()
{
    if(can_use_skill()==false)
    {
        return;
    }
    bool skill_look_canuse=false;
    if(currentrole==PLAYER)
    {
        skill_look_canuse=!skill_look_PLAYER_used;
    }
    else if(currentrole==COMPUTER)
    {
        skill_look_canuse=!skill_look_COMPUTER_used;
    }
    if((currentrole!=PLAYER)&&(currentrole!=COMPUTER)) //这段代码可以没有 只是为了补全逻辑
    {
        QMessageBox::information(this,"提示","未开局，不能使用技能");
        return;
    }
    else
    {
        if(skill_look_canuse==false)
        {

            QMessageBox::information(this,"提示","本轮看黑历史技能已经使用过，技能发动失败");
            return;
        }
        else
        {
            if(currentrole==PLAYER)
            {
                look_COMPUTER_history=true;
            }
            else if(currentrole==COMPUTER)
            {
                look_PLAYER_history=true;
            }

            QMessageBox::information(this,"技能发动成功","油菜花田白衬衫男转头照片*1");
            if (currentrole==PLAYER) //标记本轮技能已经使用
            {
                skill_look_PLAYER_used=true;
            }
            else if(currentrole==COMPUTER)
            {
                skill_look_COMPUTER_used=true;
            }
        }
    }
}

void Chessboard::setsubgamemode(SubGamemode submode)
{
    subgamemode = submode;
}

Gamemode Chessboard::getgamemode() const
{
    return gamemode;
}

SubGamemode Chessboard::getsubgamemode() const
{
    return subgamemode;
}


bool Chessboard::isboardfull() // 判断棋盘是否下满（无空点 → 和棋）
{
    for (int i = 0; i < chessboardline; i++)
    {
        for (int j = 0; j < chessboardline; j++)
        {

            if (spot[i][j] == EMPTY) // 只要还有一个空位就没满
                return false;
        }
    }
    return true;  // 遍历完都没空位 满了
}
