#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
};
#endif // MAINWINDOW_H
