#include "subwindow.h"
#include "shared.h"
#include "mainwindow.h"

subwindow::subwindow(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("五子棋模式选择界面");
    setFixedSize(450,600); //固定窗口大小

    traditionalbutton=new QPushButton("传统五子棋",this);
    traditionalbutton->move(125,300); //设置按钮位置
    traditionalbutton->setFixedSize(200,50);

    skillbutton=new QPushButton("技能五子棋",this);
    skillbutton->move(125,450); //设置按钮位置
    skillbutton->setFixedSize(200,50);

    sub_init_game(); //声明函数
    sub_load_resources();

    connect(traditionalbutton,&QPushButton::clicked,this,&subwindow::traditionalchess);
    connect(skillbutton,&QPushButton::clicked,this,&subwindow::skillchess);
}

void subwindow::sub_init_game()
{
    subview=new QGraphicsView(); //动态分配内存
    subview->setParent(this);
    subgamescene=new QGraphicsScene();
    subview->setScene(subgamescene); //subview指针指向设置场景
    subview->lower();
}

void subwindow::sub_load_resources()
{
    sub_load_startgamebackground();
}

void subwindow::sub_load_startgamebackground()
{
    subgamebackground=new QGraphicsPixmapItem();
    subgamebackground->setPixmap(QPixmap(STARTGAME_BACKGROUND));
    subgamescene->addItem(subgamebackground);
}

void subwindow::traditionalchess()
{
    MainWindow *w=new MainWindow(); //创建MainWindow类对象w
    w->show();
    w->update_mode_button(PVP,TRADITIONAL); //调用模式更新函数
    this->close();
}

void subwindow::skillchess()
{
    MainWindow *w=new MainWindow();
    w->show();
    w->getchessboard()->setsubgamemode(SKILL);
    w->update_mode_button(PVP,SKILL); //调用模式更新函数
    this->close();
}
