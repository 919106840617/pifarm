#ifndef PIGBED_H
#define PIGBED_H
#include "pig.h"

class pigbed
{
    pig* head;
    int num;
    bool black;

public:
    pigbed();
    ~pigbed();
    void add();
    void growth();
    float sell();
    int getnum();
    bool checkBlack();
};

#endif // PIGBED_H