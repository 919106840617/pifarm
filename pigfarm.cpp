#include "pigfarm.h"
#include <QtGlobal>
#include<QTime>
#include <QDebug>

pigfarm::pigfarm()
{
    int n = 0;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    n = qrand() % 1001;
    for (int i = 0; i<100; i++)
    {
        for (int j=0; j<n/100; j++)
        {
            p[i].add();
        }
    }
    for (int i = 0; i<n%100; i++)
    {
        p[i].add();
    }
}

pigfarm::~pigfarm()
{
    delete p;
}

void pigfarm::growth()
{
    for(int i =0; i<100; i++)
    {
        p[i].growth();
    }
}

float pigfarm::sell()
{
    float money = 0.0;
    for(int i=0; i<100; i++)
    {
        money += p[i].sell();
    }
    return money;
}

void pigfarm::add()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int num[11]{0};
    int n;
    int total;
    for (int i=0; i<100; i++)
    {
        n = p[i].getnum();
        num[n]++;
        total += n;
    }
    n = qrand() % (1001 - total);
    for(int i=0; i<11; i++)
    {
        if (num[i]>n)
        {
           for (int j=0; j<100; j++)
           {
               if (p[j].getnum()==i)
               {
                   p[j].add();
                   n--;
               }
               if (n==0)
                   break;
           }
        }
        else
        {
            num[i+1] += num[i];
            n -= num[i];
            for (int j=0; j<100; j++)
            {
                if (p[j].getnum()==i)
                {
                    p[j].add();
                }
            }
        }
        if (n==0)
            break;
    }
}

int* pigfarm::find(int a)
{
    return p[a].getkind();
}

bool pigfarm::check(int pigbed,int pig)
{
    return p[pigbed].getnum()>pig;
}

pig* pigfarm::getpig(int m,int n)
{
    return p[m].getpig(n);
}

int* pigfarm::get()
{
    int* ptr;
    int* n = new int[9]{0};
    for (int i=0; i<100; i++)
    {
        ptr = p[i].get();
        for (int j=0; j<9; j++)
            n[j]+=ptr[j];
        delete []ptr;
        ptr = nullptr;
    }
    return n;
}
