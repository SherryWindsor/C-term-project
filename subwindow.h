#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"
#include "shared.h"
#include "startwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class subwindow : public QWidget
{
    Q_OBJECT
public:
    explicit subwindow(QWidget *parent = nullptr);

    void sub_init_game();
    //加载函数
    void sub_load_resources();
    //开始界面的加载函数
    void sub_load_startgamebackground();

    //场景 开始游戏场景
    QGraphicsScene* subgamescene=nullptr; //初始化两个指针
    //视图
    QGraphicsView* subview=nullptr;

    QGraphicsPixmapItem* subgamebackground=nullptr;

private:
    QPushButton *traditionalbutton;
    QPushButton *skillbutton;

public slots:
    void traditionalchess();
    void skillchess();

signals:
};

#endif // SUBWINDOW_H
