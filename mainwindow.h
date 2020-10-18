#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include "pigfarm.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void update();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    pigfarm *p;
    int time;
    QTimer *timer;
};

#endif // MAINWINDOW_H
