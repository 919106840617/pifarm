#include "pig.h"
#include <QtGlobal>
#include <QTime>
#include <QDebug>

pig::pig(float w,int k)
{
    weight = w;
    kind = k;
    time = 0;
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
        qDebug() << kind << " " << weight << " " << time << endl;
        return 1;
    }
    else
        return 0;
}

void pig::setnext(pig* a)
{
    next = a;
}

pig* pig::getnext()
{
    return next;
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
