//
//  Score.h
//  helloworld
//
//  Created by 张清源 on 2020/11/25.
//

#ifndef Score_h
#define Score_h

#include <iostream>
#include <string.h>
#include "DB.h"
using namespace std;

class Score{
    string StdentNO;
    string ClassName;
    int score;
    int Tuition;
    
    Score* head; //指向头
    Score* next; //指向下一个
public:
    
    friend class User;
    
    Score(string,string);
    Score(string,string,int);
    
    int getScore();
    int getTuition();
    void changeScore(int);//输入课程和分数修改成绩
};


#endif /* Score_h */
