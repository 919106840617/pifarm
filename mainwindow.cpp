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
    p = new pigfarm();//初始化

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->setSingleShot(0);//设置加速器

    ui->lineEdit->setValidator(new QIntValidator(0, 99, this));
    ui->pigbedEdit->setValidator(new QIntValidator(0, 99, this));
    ui->pigEdit->setValidator(new QIntValidator(0, 9, this));;
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->console, &QPushButton::clicked,
            [=]()
            {
                if (timer->isActive())
                {
                    timer->stop();
                    ui->console->setText("continue");
                }
                else
                {
                    timer->start(100);
                    ui->console->setText("pause");
                }
            }
            );//开始与暂停

    {
    connect(ui->searchnum, &QPushButton::clicked,
            [=]()
            {
                ui->stackedWidget->setCurrentIndex(1);
            }
            );
    connect(ui->searchinfo, &QPushButton::clicked,
            [=]()
            {
                ui->stackedWidget->setCurrentIndex(2);
            }
            );
    connect(ui->searchtime, &QPushButton::clicked,
            [=]()
            {
                ui->stackedWidget->setCurrentIndex(3);
            }
            );
    connect(ui->return1, &QPushButton::clicked,
            [=]()
            {
                ui->stackedWidget->setCurrentIndex(0);
            }
            );
    connect(ui->return2, &QPushButton::clicked,
            [=]()
            {
                ui->stackedWidget->setCurrentIndex(0);
            }
            );
    connect(ui->return3, &QPushButton::clicked,
            [=]()
            {
                ui->stackedWidget->setCurrentIndex(0);
            }
            );
    }//换页


    connect(ui->search1, &QPushButton::clicked,
            [=]()
            {
                int n = ui->lineEdit->text().toInt();
//                qDebug() << n;
                int* numlist = p->find(n);

                ui->total->setText(QString::number(numlist[1]+numlist[2]+numlist[3]));
                ui->black->setText(QString::number(numlist[1]));
                ui->xiaohua->setText(QString::number(numlist[2]));
                ui->dahua->setText(QString::number(numlist[3]));
            }
            );

    connect(ui->search2, &QPushButton::clicked,
            [=]()
            {
                int m = ui->pigbedEdit->text().toInt();
                int n = ui->pigEdit->text().toInt();
                if (p->check(m,n))
                {
                    pig* a = p->getpig(m,n);
                    ui->weight->setText(QString::number(a->getweight()));
                    ui->time_->setText(QString::number(a->gettime()));
                    QString str;
                    switch (a->getkind()) {
                    case 1:
                        str = "黑猪";
                        break;
                    case 2:
                        str = "小花猪";
                        break;
                    case 3:
                        str = "大花白猪";
                        break;
                    default:
                        break;
                    }
                    ui->kind->setText(str);
                }
                else
                {
                    ui->weight->setText("未找到该猪");
                    ui->time_->setText("未找到该猪");
                    ui->kind->setText("未找到该猪");
                }
            }
            );

    connect(ui->search3, &QPushButton::clicked,
            [=]()
            {
                int *n = p->get();
                ui->label1->setText(QString::number(n[0]));
                ui->label2->setText(QString::number(n[1]));
                ui->label3->setText(QString::number(n[2]));
                ui->label4->setText(QString::number(n[3]));
                ui->label5->setText(QString::number(n[4]));
                ui->label6->setText(QString::number(n[5]));
                ui->label7->setText(QString::number(n[6]));
                ui->label8->setText(QString::number(n[7]));
                ui->label9->setText(QString::number(n[8]));
            }
            );


}

MainWindow::~MainWindow()
{
    delete ui;
    delete p;
    delete timer;
}

void MainWindow::update()
{
    float money =0;
    p->growth();
    time++;
    ui->time->setText(QString::number(time));
    //qDebug() << time << endl;
    if(time%91==0)
    {
        money += p->sell();
        p->add();
        //qDebug() << money;
        ui->price->setText(QString::number(money));
    }
}
