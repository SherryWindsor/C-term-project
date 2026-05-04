#include "mainwindow.h"
#include "ui_mainwindow.h"
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
}
MainWindow::~MainWindow()
{
    delete ui;
}
