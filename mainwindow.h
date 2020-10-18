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

private slots:
    void on_clear_clicked();

private:
    Ui::MainWindow *ui;

    pigfarm *p;
    int time;
    QTimer *timer;

    QString str;
    void save();
};

#endif // MAINWINDOW_H
