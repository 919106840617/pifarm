#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    time = 0;
    p = new pigfarm();
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->setSingleShot(0);
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    float money =0;
    p->growth();
    time++;
    qDebug() << time << endl;
    if(time%30==0)
    {
        money += p->sell();
        p->add();
        qDebug() << money;
        ui->price->setText(QString::number(money));
    }
}
