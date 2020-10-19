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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    pigfarm *p;
    int time, sicktime;
    QTimer *timer;

    QString str;
    void save();


    void update1();
    void update2();
    void update3();
    void update4();
};

#endif // MAINWINDOW_H
