#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"
#include "shared.h"

class StartWindow : public QWidget
{
    Q_OBJECT
public:
    explicit StartWindow(QWidget *parent = nullptr);

private:
    QPushButton *pvpButton;
    QPushButton *pveButton;

private slots:
    void startPVP();
    void startPVE();
};

#endif // STARTWINDOW_H
