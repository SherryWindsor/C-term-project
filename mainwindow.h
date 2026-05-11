#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include"chessboard.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Chessboard* getchessboard()const
    {
        return m_chessboard;
    }
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //棋盘类
    Chessboard *m_chessboard;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QPushButton *button6;
    QPushButton *button7;
    QPushButton *button8;
    QPushButton *button9;
    QPushButton *button10;
public:
    void update_mode_button(Gamemode gamemode1,SubGamemode subgamemode1);

};
#endif // MAINWINDOW_H
