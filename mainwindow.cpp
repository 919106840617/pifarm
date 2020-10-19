#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <string>
#include <QDebug>
#include <QMessageBox>
#define cout qDebug()<<"["<<__FILE__":"<<__LINE__<<"]"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("time.dat");
    if (file.exists()&&file.size())
    {
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        in >> time >> sicktime;
//        cout << time;
    }
    else
    {
        time = 0;
    }
    ui->time->setText(QString::number(time));
    p = new pigfarm();//初始化

    file.setFileName("account.txt");
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        str = in.readAll();
        file.close();
    }
    else
    {
        str = "";
    }
    //cout<<qPrintable(str);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->setSingleShot(0);//设置计时器

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
                    timer->start(10);
                    ui->console->setText("pause");
                }
            }
            );//开始与暂停


    {
    connect(ui->searchnum, &QPushButton::clicked,
            [=]()
            {
                ui->lineEdit->setText("");
                ui->total->setText("");
                ui->black->setText("");
                ui->xiaohua->setText("");
                ui->dahua->setText("");

                ui->search1->show();
                ui->stackedWidget->setCurrentIndex(1);
            }
            );
    connect(ui->searchinfo, &QPushButton::clicked,
            [=]()
            {
                ui->pigbedEdit->setText("");
                ui->pigEdit->setText("");
                ui->weight->setText("");
                ui->time_->setText("");
                ui->kind->setText("");

                ui->search2->show();
                ui->stackedWidget->setCurrentIndex(2);
            }
            );
    connect(ui->searchtime, &QPushButton::clicked,
            [=]()
            {
                ui->stackedWidget->setCurrentIndex(3);
                update3();
                connect(timer, &QTimer::timeout, this, &MainWindow::update3);
            }
            );
    connect(ui->return1, &QPushButton::clicked,
            [=]()
            {
                disconnect(timer, &QTimer::timeout, this, &MainWindow::update1);
                ui->stackedWidget->setCurrentIndex(0);
            }
            );
    connect(ui->return2, &QPushButton::clicked,
            [=]()
            {
                disconnect(timer, &QTimer::timeout, this, &MainWindow::update2);

                ui->stackedWidget->setCurrentIndex(0);
            }
            );
    connect(ui->return3, &QPushButton::clicked,
            [=]()
            {
                disconnect(timer, &QTimer::timeout, this, &MainWindow::update3);

                ui->stackedWidget->setCurrentIndex(0);
            }
            );
    }//换页


    {
    connect(ui->search1, &QPushButton::clicked,
            [=]()
            {
                update1();
                ui->search1->hide();
                connect(timer, &QTimer::timeout, this, &MainWindow::update1);
            }
            );//查询某猪圈

    connect(ui->search2, &QPushButton::clicked,
            [=]()
            {
                update2();
                ui->search2->hide();
                connect(timer, &QTimer::timeout, this, &MainWindow::update2);
            }
            );//查询某猪
    }//查询

    update4();
}

MainWindow::~MainWindow()
{
    save();
    delete ui;
    delete p;
    delete timer;
}

void MainWindow::update()
{
    p->growth();
    p->sickSpread();
    time++;
    if (p->getSickNum())
        sicktime++;
    ui->time->setText(QString::number(time));
    //qDebug() << time << endl;
    if(time%91==0)
    {
        float money =0;
        money += p->sell();
        p->add();
        //qDebug() << money;
        ui->price->setText(QString::number(money,'f',0));

        str += "day" + QString::number(time) + ": " + QString::number(money,'f',0) + "\n";
        if (time>5*365)
        {
            int n = 0;
            while (str.at(n) != '\n')
                n++;
            str.remove(0,n+1);
        }
        //cout << qPrintable(str);
    }
    update4();
}

void MainWindow::on_clear_clicked()
{
    timer->stop();
    ui->console->setText("start");
    ui->stackedWidget->setCurrentIndex(0);

    delete p;
    time = 0;
    sicktime = 0;
    ui->time->setText(QString::number(time));
    ui->price->setText("");

    QFile file("save.dat");
    if (file.exists())
    {
        file.remove();
    }
    file.setFileName("account.txt");
    if (file.exists())
    {
        file.remove();
    }
    file.setFileName("time.dat");
    if (file.exists())
    {
        file.remove();
    }

    str = "";
    p = new pigfarm();
    update4();
}

void MainWindow::save()
{
    QFile file("time.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << time << sicktime;
    file.close();

    file.setFileName("account.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream textout(&file);
    textout << str;
    file.close();
}

void MainWindow::update1()
{
    int n = ui->lineEdit->text().toInt();
    int* numlist = p->find(n);
    ui->total->setText(QString::number(numlist[1]+numlist[2]+numlist[3]));
    ui->black->setText(QString::number(numlist[1]));
    ui->xiaohua->setText(QString::number(numlist[2]));
    ui->dahua->setText(QString::number(numlist[3]));
}

void MainWindow::update2()
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

void MainWindow::update3()
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

void MainWindow::on_pushButton_clicked()
{
    p->sickStart(50);
    sicktime = 0;
    update4();
}

void MainWindow::update4()
{
    ui->label_26->setText(QString::number(p->getTotalNum()));
    ui->label_27->setText(QString::number(p->getSickNum()));
    ui->label_28->setText(QString::number(p->getDeadNum()));
    ui->label_30->setText(QString::number(sicktime));
}

void MainWindow::on_pushButton_2_clicked()
{
    p->sickOver();
}

void MainWindow::on_pushButton_3_clicked()
{
    if (str=="")
        QMessageBox::information(0 , "销售记录", "最近无销售记录", QMessageBox::Ok | QMessageBox::Default, 0,  0 );
    else
       QMessageBox::information(0 , "销售记录", str, QMessageBox::Ok | QMessageBox::Default, 0,  0 );
}
