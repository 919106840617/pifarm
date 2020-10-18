#ifndef PIGFARM_H
#define PIGFARM_H
#include "pigbed.h"

class pigfarm
{
    pigbed *p = new pigbed[100]();
    int blackbed;
public:
    pigfarm();
    void growth();
    float sell();
    void add();
};

#endif // PIGFARM_H
