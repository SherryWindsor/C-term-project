#include "startwindow.h"
#include "shared.h"
#include "subwindow.h"
#include <QVBoxLayout>

StartWindow::StartWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("五子棋开始界面"); //设置名称
    setFixedSize(450,600); //设置主界面窗口大小
    // 创建按钮
    pvpButton=new QPushButton("PVP - 人人对战", this);
    pvpButton->move(125,300);
    pvpButton->setFixedSize(200,50);

    pveButton=new QPushButton("PVE - 人机对战", this);
    pveButton->move(125,450);
    pveButton->setFixedSize(200,50);

    init_game();
    load_resources();

    // 信号槽连接
    connect(pvpButton,&QPushButton::clicked,this,&StartWindow::startPVP);
    connect(pveButton,&QPushButton::clicked,this,&StartWindow::startPVE);
}

void StartWindow::init_game()
{
    view=new QGraphicsView(); //动态分配内存
    view->setParent(this); //令view成为startwindow的子组件 而不是创建一个新窗口
    startgamescene=new QGraphicsScene();
    view->setScene(startgamescene); //view指针指向设置场景
    view->lower();
}

void StartWindow::load_resources()
{
    load_startgamebackground();
}

void StartWindow::load_startgamebackground()
{
    startgamebackground=new QGraphicsPixmapItem();
    startgamebackground->setPixmap(QPixmap(STARTGAME_BACKGROUND));
    startgamescene->addItem(startgamebackground);
}

void StartWindow::startPVP()
{
    subwindow *w=new subwindow();
    w->show();
    this->close();
}

void StartWindow::startPVE()
{
    MainWindow *w=new MainWindow(); //主界面链接人机模式棋盘界面
    w->show();

    // 设置棋盘模式为 PVE
    w->getchessboard()->setgamemode(PVE);
    w->getchessboard()->setsubgamemode(TRADITIONAL); //此处设定只为给函数传参 与模式无关
    w->update_mode_button(PVE,TRADITIONAL); //调用模式更新函数
    this->close();
}
