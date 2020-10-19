#include "pig.h"
#include <QtGlobal>
#include <QTime>
#include <QDebug>
#define cout qDebug()<<"["<<__FILE__":"<<__LINE__<<"]"

pig::pig(float w,int k)
{
    weight = w;
    kind = k;
    time = 0;
    sick = false;
    next = nullptr;
}

void pig::growth()
{
    time++;
    weight+=qrand() * 2.4 / double(RAND_MAX);
}

bool pig::judge()
{
    if (time > 365 || weight >150)
    {
        //qDebug() << kind << " " << weight << " " << time << endl;
        return true;
    }
    else
        return false;
}

void pig::setnext(pig* a)
{
    next = a;
}

pig* pig::getnext()
{
    return next;
}

int pig::getkind()
{
    return kind;
}

float pig::getprice()
{
    switch (kind) {
    case 1:
        return weight * 15;
        break;
    case 2:
        return weight * 7;
        break;
    case 3:
        return weight * 6;
        break;
    default:
        return 0.0;
        break;
    };
}

float pig::getweight()
{
    return weight;
}
int pig::gettime()
{
//    qDebug() << weight << " " << time << " " << kind;
    return time;
}

pig::pig(int k, int t, float w)
{
    kind = k;
    time = t;
    weight = w;
    sick = false;
    next = nullptr;
}


void pig::getsick()
{
    sick = true;
}

bool pig::isSick()
{
    return sick;
}
