#ifndef PIGBED_H
#define PIGBED_H
#include "pig.h"

class pigbed
{
    pig* head;
    pig* last;
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

    int* getkind();
    pig* getpig(int);
    int* get();

    void add(int, int, float);
    void over();
};

#endif // PIGBED_H
