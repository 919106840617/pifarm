#include "pigbed.h"
#include <QtGlobal>
#include <QTime>
#include <QDebug>
int hua()
{
    return qrand() % 2 + 2;
}

pigbed::pigbed()
{
    head = nullptr;
    num = 0;
    black = 0;
}

pigbed::~pigbed()
{
    pig* p = nullptr;
    while (head != nullptr)
    {
        p = head;
        head = head->getnext();
        delete []p;
    }
    p = nullptr;
}

void pigbed::add()
{
    pig *p;
    float w =qrand() * 60 / double(RAND_MAX) + 40.0;
    int k;
    if (head == nullptr)
    {
        k = qrand() % 3 + 1;
        head = new pig(w,k);
        if(k==1)
            black = 1;
        else
            black = 0;
    }
    else
    {
        if (black)
            p = new pig(w,1);
        else
            p = new pig(w,hua());
        p->setnext(head);
        head = p;
    }
    num++;
}

void pigbed::growth()
{
    pig* p = head;
    while (p != nullptr)
    {
        p->growth();
        p = p->getnext();
    }
}

float pigbed::sell()
{
    float money = 0.0;
    if (head == nullptr)
        return money;
    pig *p;
    while (head!=nullptr && head->judge())
    {
        money += head->getprice();
        p = head;
        head = head->getnext();
        delete []p;
        num--;
    }
    if (head == nullptr)
        return money;
    pig* prep = head;
    p = head->getnext();
    while (p!=nullptr)
    {
        if (p->judge())
        {
            money += p->getprice();
            prep->setnext(p->getnext());
            delete []p;
            num--;
            p = prep->getnext();
            continue;
        }
        prep = prep->getnext();
        p = p->getnext();
    }
    return money;
}

int pigbed::getnum()
{
    return num;
}

bool pigbed::checkBlack()
{
    return black;
}

int* pigbed::getkind()
{
    int* n = new int[4]{0};
    pig* p = head;
    while (p!=nullptr)
    {
        n[p->getkind()]++;
        p = p->getnext();
    }
//    for (int i=1; i<4; i++)
//    {
//        qDebug() << n[i] << " ";
//    }
    return n;
}

pig* pigbed::getpig(int n)
{
    pig* p = head;
    for (int i=0; i<n; i++)
    {
        p = p->getnext();
    }
    return p;
}

int* pigbed::get()
{
    int* n = new int[9]{0};

    pig* p = head;
    float weight;
    int time;
    while (p!=nullptr)
    {
        weight = p->getweight();
        time = p->gettime();

        n[p->getkind()-1]++;
        if (weight<=100.0)
            n[3]++;
        else if (weight<=150.0)
            n[4]++;
        else
            n[5]++;

        if (time<=90)
            n[6]++;
        else if (time<=180)
            n[7]++;
        else
            n[8]++;

        p = p->getnext();
    }
    return n;
}
