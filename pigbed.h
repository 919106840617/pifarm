#ifndef PIGBED_H
#define PIGBED_H
#include "pig.h"

class pigbed
{
    pig* head;
    pig* last;
    int num;
    bool black;

    int sick;
    int deadprobability;
    int dead;

public:
    pigbed();
    ~pigbed();
    void add();
    void add(int k, float w);
    void growth();
    float sell();
    int getnum();
    bool checkBlack();

    int* getkind();
    pig* getpig(int);
    int* get();

    void addback(int k, int t, float w, bool s);
    void over();

    void diseaseSpread();
    void PigGetSick();
    int getSickNum();
    void setDeadProbability(int p);
    int getDeadProbability();
    void sickToDeath();
    int getDeadNum();
    void setDeadNum(int n);
    void startSick();
    void sickOver();
};

#endif // PIGBED_H
