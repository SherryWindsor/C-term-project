#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"
#include "shared.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class StartWindow : public QWidget
{
    Q_OBJECT
public:
    explicit StartWindow(QWidget *parent = nullptr);

    void init_game();
    //加载函数
    void load_resources();
    //开始界面的加载函数
    void load_startgamebackground();

    //场景 开始游戏场景
    QGraphicsScene* startgamescene=nullptr; //初始化两个指针
    //视图
    QGraphicsView* view=nullptr;

    QGraphicsPixmapItem* startgamebackground=nullptr;

private:
    QPushButton *pvpButton;
    QPushButton *pveButton;

private slots:
    void startPVP();
    void startPVE();
};

#endif // STARTWINDOW_H
