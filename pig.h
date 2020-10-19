#ifndef PIG_H
#define PIG_H

class pig
{
    float weight;//斤
    int time;
    int kind;//1黑2小花3大花白
    bool sick;
    pig* next;

public:
    pig(float,int);
    void growth();
    bool judge();
    void setnext(pig*);
    pig* getnext();
    int getkind();
    float getprice();

    float getweight();
    int gettime();

    pig(int, int, float);

    void getsick();
    bool isSick();
};

#endif // PIG_H
