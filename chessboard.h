#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include "shared.h"

#define MAXSTEP 225 //共225个可能下棋的点

class Chessboard : public QWidget //继承
{
    Q_OBJECT
public:
    explicit Chessboard(QWidget *parent = nullptr);

    // 设置游戏模式（通过公共方法）
    void setgamemode(Gamemode mode);
    void setsubgamemode(SubGamemode submode);

    Gamemode getgamemode() const; //由于下方的gamemode和subgamemode两个变量是私有的 故此处设置读取游戏模式（通过公有方法）
    SubGamemode getsubgamemode()const; //用const保证此处只能读取数据 而不能更改数据

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
    Gamemode gamemode=PVP; //初始化游戏模式
    Role currentrole=PLAYER;
    SubGamemode subgamemode=TRADITIONAL;
    //不同功能的函数
private:
    int historyrow[MAXSTEP]; //上一次落子的行 （最多225次落子）
    int historycol[MAXSTEP]; //上一次落子的列
    Role historyrole[MAXSTEP]; //上一次落子的对象
    int historycount; //记录上一次落子是全局中的第几次

    void recordstep(int row,int col,Role role3);
    void regretstep();

private:
    bool isboardfull();

    int opponentrow[MAXSTEP]; //对手落子的行（最多225次落子）
    int opponentcol[MAXSTEP]; //对手落子的列

    bool keepcurrentrole=false;

    bool click_fly_baseball=false;

    int cleaningrow[MAXSTEP]; //对手落子的行
    int cleaningcol[MAXSTEP]; //对手落子的列

    int emptyrow[MAXSTEP]; //没有填入棋子的行
    int emptycol[MAXSTEP]; //没有填入棋子的列

    int lookrow[MAXSTEP];
    int lookcol[MAXSTEP];

    bool can_use_skill();
    bool cannot_use_skill=false; //初始化bool型变量 默认所有玩家都可以使用技能

    bool look_PLAYER_history=false;
    bool look_COMPUTER_history=false;

    bool skill_fly_PLAYER_used; //标记黑棋本轮是否用过飞沙走石
    bool skill_fly_COMPUTER_used; //标记白棋本轮是否用过飞沙走石
    bool skill_strength_PLAYER_used; //标记黑棋本轮是否用过力拔山兮
    bool skill_strength_COMPUTER_used; //标记白棋本轮是否用过力拔山兮
    bool skill_still_PLAYER_used; //标记黑棋本轮是否用过静如止水
    bool skill_still_COMPUTER_used; //标记白棋本轮是否用过静如止水
    bool skill_baseball_PLAYER_used; //标记黑棋本轮是否用过这是棒球
    bool skill_baseball_COMPUTER_used; //标记白棋本轮是否用过这是棒球
    bool skill_cleaning_PLAYER_used; //标记黑棋本轮是否用过我是保洁
    bool skill_cleaning_COMPUTER_used; //标记白棋本轮是否用过我是保洁
    bool skill_seize_PLAYER_used; //标记黑棋本轮是否用过擒拿擒拿
    bool skill_seize_COMPUTER_used; //标记白棋本轮是否用过擒拿擒拿
    bool skill_find_PLAYER_used; //标记黑棋本轮是否用过拾金不昧
    bool skill_find_COMPUTER_used; //标记白棋本轮是否用过拾金不昧
    bool skill_look_PLAYER_used; //标记黑棋本轮是否使用过看黑历史
    bool skill_look_COMPUTER_used; //标记白棋本轮是否使用过看黑历史

public slots:
    void regret(); //悔棋槽函数 方便链接按钮
    void draw(); //和棋槽函数 方便链接按钮
    void fly_sand_go_stone(); //飞沙走石槽函数 方便链接按钮
    void strength_uproot_mountain(); //力拔山兮槽函数 方便链接按钮
    void still_like_stagnant_water(); //静如止水槽函数 方便链接按钮
    void this_is_baseball(); //这是棒球槽函数 方便链接按钮
    void i_am_cleaning(); //我是保洁槽函数 方便链接按钮
    void seize_hold(); //擒拿擒拿槽函数 方便链接按钮
    void find_gold_no_hide(); //拾金不昧槽函数 方便链接按钮
    void look_at_embarrassing_history(); //看黑历史槽函数 方便链接按钮
signals:
};

#endif // CHESSBOARD_H
