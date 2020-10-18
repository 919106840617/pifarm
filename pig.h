#ifndef PIG_H
#define PIG_H

class pig
{
    float weight;//斤
    int time;
    int kind;//1黑2小花3大花白
    pig* next;

public:
    pig(float,int);
    void growth();
    bool judge();
    void setnext(pig*);
    pig* getnext();
    float getprice();
};

#endif // PIG_H
