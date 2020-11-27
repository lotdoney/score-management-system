//
//  main.cpp
//  helloworld
//
//  Created by 张清源 on 2020/11/25.
//

//
//  main.cpp
//  xscjglxt
//
//  Created by Lin Zehao on 1/12/15.
//  Copyright (c) 2015 Lin Zehao. All rights reserved.
//

#include "Admin.h"

int main() {
    
    int login_flag = 0;
    int passTry = 0;
    User TmpStudent;
    Admin admin;
    int exit_flag = 0;
    
    while(!login_flag){
        cout<<"-----学生成绩管理系统-----"<<endl;
        cout<<"-----------------------"<<endl;
        cout<<"---------登录界面--------"<<endl;
        cout<<"--请输入ID(输入0退出程序）--"<<endl;
        
        string TmpUserNo;
        cin>>TmpUserNo;
        
        if(TmpUserNo=="0")
            return 0;
        
        
        cout<<"--------请输入密码--------"<<endl;
        
        string TmpPasswd;
        cin>>TmpPasswd;
        
        if(admin.IDVertify(TmpUserNo,TmpPasswd)){
            TmpStudent.setUser(TmpUserNo);
            login_flag=1;
        }
        
        else{
            passTry++;
        }
        
        if(passTry==5){
            cout<<"您尝试的次数过多，请详询管理员"<<endl;
            return 0;
        }
        
    }
    
    int TmpUserType;
    TmpUserType=TmpStudent.getUserType();
    
    while(exit_flag==0){
        if(TmpUserType!=1&&TmpUserType!=4)
        {
            cout<<"------以下是您的信息-----"<<endl;
            TmpStudent.showInfo();
            
            cout<<"------输入1退出程序------"<<endl;
            cin>>exit_flag;
        }
        
        else if(TmpUserType ==4){
            int t_select;
            cout <<"------老师您好------"<<endl;
            cout <<"------1:查询成绩------\n------0.退出程序------"<<endl;
            cin >>t_select;
            if(t_select == 1){
                cout<<"-------成绩查询-------\n------请输入查询内容-------"<<endl;
                int chaxun=1;
                while (chaxun!=0) {
                    cout<<"1.课程成绩\n2.学生成绩\n0.退出查询\n"<<endl;
                    cin>>chaxun;
                    switch (chaxun) {
                        case 1:{
                            cout<<"----请输入查询的课程----"<<endl;
                            string Kecheng;
                            cin>>Kecheng;
                            admin.ShowAllScore(Kecheng);
                        }
                            break;
                        case 2:{
                            string newNO = admin.SearchUser();
                            if (newNO!="不存在") {
                                User newUser(newNO);
                                newUser.showInfo();
                            }


                    }

                    }
            }

            }
            
            else if (t_select==0){
                exit_flag =1;
            }
            
            
      }
            
            
        else if (TmpUserType ==1){
            int select;
            cout<<"--------教务管理员您好---------"<<endl;
            cout<<"--------请选择功能-------"<<endl;
            cout<<"1:登记成绩\n2:成绩查询\n3.成绩修改\n4.添加(删除,修改)学生\n5.添加(删除)课程\n0.退出程序\n"<<endl;
            
            cin>>select;
            
            switch (select) {
                case 1:{
                    cout<<"-------成绩登记-------"<<endl;
                    admin.ScoreEntering();
                }
                    break;
                    
                case 2:{
                    cout<<"-------成绩查询-------\n------请输入查询内容-------"<<endl;
                    int chaxun=1;
                    
                    while (chaxun!=0) {
                        cout<<"1.课程成绩\n2.学生成绩\n0.退出查询\n"<<endl;
                        cin>>chaxun;
                        switch (chaxun) {
                            case 1:{
                                cout<<"----请输入查询的课程----"<<endl;
                                string Kecheng;
                                cin>>Kecheng;
                                admin.ShowAllScore(Kecheng);
                            }
                                
                                break;
                                
                            case 2:{
                                string newNO = admin.SearchUser();
                                if (newNO!="不存在") {
                                    User newUser(newNO);
                                    newUser.showInfo();
                                }
                                
                            }
                                
                                break;
                                
                            default:
                                break;
                        }
                        
                    }
                }
            
                    
                    
                    break;
                    
                    
                case 3:{
                    cout<<"-----成绩修改-----\n------请输入修改内容-------"<<endl;
                    int xiugai=1;
                    
                    while (xiugai!=0) {
                        cout<<"1.重新录入\n2.指定学生成绩\n0.退出修改\n"<<endl;
                        cin>>xiugai;
                        switch (xiugai) {
                            case 1:{
                                admin.ScoreEntering();
                            }
                                break;
                                
                            case 2:{
                                string studentno = admin.SearchUser();
                                if(studentno!="不存在"){
                                    User newUser(studentno);
                                    newUser.showInfo();
                                    
                                    cout<<"请输入课程："<<endl;
                                    string newClass;
                                    cin>>newClass;
                                    
                                    cout<<"请输入成绩："<<endl;
                                    int score;
                                    string TmpStr;
                                    cin>>score;
                                    
                                    newUser.cSScore(newClass,score);
                                }
                                
                            }
                                
                                break;
                                
                            default:
                                break;
                        }
                        
                    }
                }
                    
                    
                    break;
                
                    
                case 4:{
                    cout<<"----添加(删除，修改)学生----"<<endl;
                    int xuesheng=1;
                    
                    while (xuesheng!=0) {
                        cout<<"1.添加学生\n2.删除学生\n3.修改学生信息\n0.退出修改\n"<<endl;
                        cin>>xuesheng;
                        switch (xuesheng)
                        {
                            case 1:{
                                admin.AddUser();
                            }
                                
                                break;
                                
                            case 2:{
                                admin.DelUser();
                            }
                                
                                break;
                                
                            case 3:{
                                string chNo = admin.SearchUser();
                                if (chNo!="不存在") {
                                    admin.ChaUser(chNo);
                                }
                                
                                else
                                    cout<<"用户不存在或修改失败"<<endl;
                            }
                                
                            default:
                                break;
                        }
                        
                    }
                }
                    
                    
                    break;
                    
                
                case 5:{
                    cout<<"----添加(删除)课程----"<<endl;
                    int kecheng=1;
                    
                    while (kecheng!=0) {
                        cout<<"1.添加课程\n2.删除课程\n0.退出修改\n"<<endl;
                        cin>>kecheng;
                        switch (kecheng)
                        {
                            case 1:{
                                admin.AddClass();
                            }
                                
                                break;
                                
                            case 2:{
                                admin.DelClass();
                            }
                                
                                break;
                                
                            default:
                                break;
                        }
                        
                    }
                }
                    
                    
                    break;
                    
                case 0:{
                    exit_flag = 1;
                }
                    
                default:
                    break;
            }
            
        }

    }
    
    
    
    }

