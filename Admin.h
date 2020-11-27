//
//  Admin.h
//  helloworld
//
//  Created by 张清源 on 2020/11/25.
//

#ifndef Admin_h
#define Admin_h

//
//  Admin.h
//  xscjglxt
//
//  Created by Lin Zehao on 1/12/15.
//  Copyright (c) 2015 Lin Zehao. All rights reserved.
//

//#ifndef __xscjglxt__Admin__
//#define __xscjglxt__Admin__

#include <iostream>
#include <string>
#include "User.h"
#include "DB.h"
using namespace std;

class Admin{
    User TmpUser;
public:
    //Admin();
    //~Admin();
    
    void ScoreEntering(); //成绩录入
    
    bool IDVertify(string,string);//检查登录信息

    void AddUser(); //添加用户
    void DelUser(); //删除用户
    void AddClass();
    void DelClass();//删除课程
    
    void ChaUser(string); //修改用户信息(包括成绩）
    
    void ShowAllScore(string); //显示所有学生某门课程的成绩
    
    string SearchUser(); //查询学生,返回学号;
    
    
};

//#endif /* defined(__xscjglxt__Admin__) */




#endif /* Admin_h */
