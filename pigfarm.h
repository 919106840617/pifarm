#ifndef PIGFARM_H
#define PIGFARM_H
#include "pigbed.h"

class pigfarm
{
    pigbed *p = new pigbed[100];
    int blackbed;
public:
    pigfarm();
    ~pigfarm();
    void growth();
    float sell();
    void add();

    int* find(int);
    bool check(int,int);
    pig* getpig(int,int);
    int* get();
};

#endif // PIGFARM_H
