#include "pigbed.h"
#include <QtGlobal>
#include<QTime>

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
