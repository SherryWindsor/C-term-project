#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shared.h"
#include "chessboard.h"

//垂直布局所需头文件
#include<QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //指针
    ui->setupUi(this);
    //固定棋盘大小 15（格子数）*40（格子大小）+2（上下）*20(边缘)
    setFixedSize(1000,640);
    //设置窗口标题
    setWindowTitle("五子棋");
    //创建棋盘对象
    m_chessboard=new Chessboard(this);
    //截止至此 创建出的棋盘极小（只有左上角）
    //设置布局
    QWidget * centerWidget=new QWidget(this);
    setCentralWidget(centerWidget);
    //以下类需QVBoxLayout头文件
    //将布局设置在centralWidget上
    QVBoxLayout*mylayout=new QVBoxLayout(centerWidget);
    //将棋盘控件添加到垂直布局中去，让布局管理器管理它的位置和大小
    mylayout->addWidget(m_chessboard);

    button1=new QPushButton("悔棋",this);
    button1->move(650,100);
    connect(button1,&QPushButton::clicked,m_chessboard,&Chessboard::regret);

    button2=new QPushButton("和棋",this);
    button2->move(800,100);
    connect(button2,&QPushButton::clicked,m_chessboard,&Chessboard::draw);

    button3=new QPushButton("飞沙走石",this);
    button3->move(650,100);
    connect(button3,&QPushButton::clicked,m_chessboard,&Chessboard::fly_sand_go_stone);

    button4=new QPushButton("力拔山兮",this);
    button4->move(800,100);
    connect(button4,&QPushButton::clicked,m_chessboard,&Chessboard::strength_uproot_mountain);

    button5=new QPushButton("静如止水",this);
    button5->move(650,200);
    connect(button5,&QPushButton::clicked,m_chessboard,&Chessboard::still_like_stagnant_water);

    button6=new QPushButton("这叫棒球",this);
    button6->move(800,200);
    connect(button6,&QPushButton::clicked,m_chessboard,&Chessboard::this_is_baseball);

    button7=new QPushButton("保洁上门",this);
    button7->move(650,300);
    connect(button7,&QPushButton::clicked,m_chessboard,&Chessboard::i_am_cleaning);

    button8=new QPushButton("擒拿擒拿",this);
    button8->move(800,300);
    connect(button8,&QPushButton::clicked,m_chessboard,&Chessboard::seize_hold);

    button9=new QPushButton("拾金不昧",this);
    button9->move(650,400);
    connect(button9,&QPushButton::clicked,m_chessboard,&Chessboard::find_gold_no_hide);

    button10=new QPushButton("看黑历史",this);
    button10->move(800,400);
    connect(button10,&QPushButton::clicked,m_chessboard,&Chessboard::look_at_embarrassing_history);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_mode_button(Gamemode gamemode1, SubGamemode subgamemode1)
{
    Gamemode gamemode_window=m_chessboard->getgamemode();  //getgamemode() 是 Chessboard 类的成员函数 不能直接写 getgamemode() 调用 必须通过 棋盘对象的指针 m_chessboard 来调用
    SubGamemode subgamemode_window=m_chessboard->getsubgamemode(); //为了防止在最初始的条件下就直接进行按钮的隐藏和显示（初始条件为PVP TRADITIONAL） 故写函数 在按完按钮后调用此函数进行参数的更新 从而正确地按照玩家的模式选择进行按钮的隐藏和显示
    if(button1)
    {
        button1->hide();
    }
    if(button2)
    {
        button2->hide();
    }
    if(button3)
    {
        button3->hide();
    }
    if(button4)
    {
        button4->hide();
    }
    if(button5)
    {
        button5->hide();
    }
    if(button6)
    {
        button6->hide();
    }
    if(button7)
    {
        button7->hide();
    }
    if(button8)
    {
        button8->hide();
    }
    if(button9)
    {
        button9->hide();
    }
    if(button10)
    {
        button10->hide();
    }
    if(gamemode_window==PVE||(gamemode_window==PVP&&subgamemode_window==TRADITIONAL))
    {
        button1->show();
        button2->show();
    }
    else
    {
        button3->show();
        button4->show();
        button5->show();
        button6->show();
        button7->show();
        button8->show();
        button9->show();
        button10->show();
    }
}
