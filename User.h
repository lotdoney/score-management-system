//
//  User.h
//  helloworld
//
//  Created by 张清源 on 2020/11/25.
//

#ifndef User_h
#define User_h

#include <iostream>
#include <string.h>
#include "Score.h"
#include "DB.h"
using namespace std;

class User{
    int UserType; //1老师，2本科生，3研究生，4博士生，0未定

    string StudentNo; //学号
    string sname;//姓名
    string spassword;//密码
    Score* sscore; //分数
    Score* sstail; //分数

public:
    User():UserType(0),StudentNo("暂无"),sname("暂无"),spassword("暂无"),sscore(nullptr),sstail(nullptr){}
    User(string);
    ~User();
    
    void setUser(string);
    
    int getUserType() const;
    
    string getStudentNo() const;
    string getName() const;
    string getPassword() const;
    Score* getScore() const;
    
    void showInfo();
    
    void cStudentNo(string);
    void cSName(string);
    void cSPassword(string);
    void cSScore(string,int);
    
    
    
};



#endif /* User_h */
