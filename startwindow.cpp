#include "startwindow.h"
#include "shared.h"
#include <QVBoxLayout>

StartWindow::StartWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("五子棋开始界面");

    // 创建按钮
    pvpButton=new QPushButton("PVP - 人人对战", this);
    pveButton=new QPushButton("PVE - 人机对战", this);

    // 布局
    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(pvpButton);
    layout->addWidget(pveButton);
    setLayout(layout);

    // 信号槽连接
    connect(pvpButton,&QPushButton::clicked,this,&StartWindow::startPVP);
    connect(pveButton,&QPushButton::clicked,this,&StartWindow::startPVE);
}

void StartWindow::startPVP()
{
    MainWindow *w=new MainWindow();
    w->show();
    this->close();
}

void StartWindow::startPVE()
{
    MainWindow *w=new MainWindow(); //主界面链接人机模式棋盘界面
    w->show();

    // 设置棋盘模式为 PVE
    w->getchessboard()->setgamemode(PVE);

    this->close();
}
