//
//  Admin.cpp
//  helloworld
//
//  Created by 张清源 on 2020/11/25.
//


#include <fstream>
#include <string>
#include "Admin.h"

void Admin::ScoreEntering(){
    cout<<"----成绩录入系统-----"<<endl;
    cout<<"请选择录入方式："<<endl;
    cout<<"1:文件录入\n2:单个录入\n其它任意返回"<<endl;
    int xuanze;
    cin>>xuanze;
    
    switch (xuanze) {
        case 1:{
            cout<<"请输入课程："<<endl;
            string newClass;  // 输入课程
            cin>>newClass;
            cout<<"请输入文件绝对的路径："<<endl;
            char * filename;
            
            cin.getline(filename, 100);
            
            
            
            ifstream ocin;
            ocin.open(filename);
            
            string str;
            string StudentNo; //学号
            int score; //分数
            while ( !ocin.eof() ) {
                ocin>>StudentNo;
                ocin>>score;
                User newUser(StudentNo);
                newUser.cSScore(newClass,score);
                
            }
            
        }
        
        case 2:{
            cout<<"请输入学生学号："<<endl;
            string StudentNo;
            cin>>StudentNo;
            User newUser(StudentNo);
            
            int newUserType = newUser.getUserType();
            if (newUserType == 0) {
                cout<<endl;
            } else if (newUserType == 4) {
                cout<<"无法修改教师成绩！\n"<<endl;
            } else {
                newUser.showInfo();
                
                cout<<"请输入课程："<<endl;
                string newClass;
                cin>>newClass;
                Score newScore(StudentNo,newClass);
                cout<<"请输入成绩："<<endl;
                int score;
                cin>>score;
            
//                if (newScore.getTuition()==1) {
//                    newUser.cSScore(newClass,score);
//                }
             
                    cout << "未缴纳本课程费用，无法登记成绩，请尽快交费！" <<endl;
                
                
            }
        }
            
            break;
            
        default:
            break;
    }
}


bool Admin::IDVertify(string name,string number){
    DB database;
    sprintf(database.mquery, "SELECT password FROM users WHERE id='%s'", name.c_str());
    mysql_query(database.conn, database.mquery);
    database.res = mysql_use_result(database.conn);
    if (database.res) {
        database.row = mysql_fetch_row(database.res);
        if (database.row) {
            if(!number.compare(*database.row)) {
                return true;
            } else {
                cout<<"----错误的用户名或密码----\n"<<endl;
            }
        } else {
            cout<<"------用户名不存在------\n"<<endl;
        }
    }
    return false;
}

void Admin::AddUser(){
    cout<<"-----添加新用户-----"<<endl;
    cout<<"---请输入用户类型---"<<endl;
    cout<<"1：教师\n2：本科生\n3：研究生\n4：教务管理"<<endl;
    int newType;
    cin>>newType;
    
    
    cout<<"-请输入用户学号（工号）-"<<endl;
    string newNO;
    cin>>newNO;
    
    DB database;
    sprintf(database.mquery, "SELECT * FROM users WHERE id='%s'", newNO.c_str());
    mysql_query(database.conn, database.mquery);
    database.res = mysql_use_result(database.conn);
    database.row = mysql_fetch_row(database.res);
    if (database.row) {
        cout<<"----用户已存在----"<<endl;
    } else {
        cout<<"----请输入姓名----"<<endl;
        string newName;
        cin>>newName;
        cout<<"----请输入密码----"<<endl;
        string newPass;
        cin>>newPass;
        sprintf(database.mquery, "INSERT INTO users (id, name, usertype, password) VALUES ('%s', '%s', %d, '%s');", newNO.c_str(), newName.c_str(), newType, newPass.c_str());
        mysql_query(database.conn, database.mquery);
        if (!mysql_errno(database.conn)) {
            cout<<"操作成功"<<endl;
        } else {
            cout<<"操作失败"<<endl;
            cout<<"Insert error: #"<<mysql_errno(database.conn)<<" "<<mysql_error(database.conn)<<endl;
            return;
        }
        mysql_free_result(database.res);
        DB classdb;
        sprintf(database.mquery, "SELECT DISTINCT classname FROM score;");
        mysql_query(database.conn, database.mquery);
        database.res = mysql_use_result(database.conn);
        database.row = mysql_fetch_row(database.res);
        if (database.row) {
            sprintf(classdb.mquery, "INSERT INTO score (classname, stuid) VALUES ('%s', '%s');", database.row[0], newNO.c_str());
            mysql_query(classdb.conn, classdb.mquery);
            while((database.row = mysql_fetch_row(database.res))) {
                sprintf(classdb.mquery, "INSERT INTO score (classname, stuid) VALUES ('%s', '%s');", database.row[0], newNO.c_str());
                mysql_query(classdb.conn, classdb.mquery);
            }
        } else {
            cout<<"---数据库中无课程---"<<endl;
        }
    }
}

void Admin::DelUser(){
    cout<<"-----删除用户-----"<<endl;
    string delNo = SearchUser();
    if (delNo!="不存在") {
        User delUser(delNo);
        
        if(delUser.getStudentNo()==TmpUser.getStudentNo()){
            cout<<"不能删除自己！！"<<endl;
        }
        else
        {
            DB database;
            sprintf(database.mquery, "DELETE FROM users WHERE id=%s", delNo.c_str());
            mysql_query(database.conn, database.mquery);
            if (mysql_errno(database.conn)) {
                cout<<"操作失败"<<endl;
                cout<<"Delete error: #"<<mysql_errno(database.conn)<<" "<<mysql_error(database.conn)<<endl;
                return;
            }
            sprintf(database.mquery, "DELETE FROM score WHERE stuid=%s", delNo.c_str());
            mysql_query(database.conn, database.mquery);
            if (mysql_errno(database.conn)) {
                cout<<"操作失败"<<endl;
                cout<<"Delete error: #"<<mysql_errno(database.conn)<<" "<<mysql_error(database.conn)<<endl;
                return;
            }
            cout<<"操作成功"<<endl;
        }
        
    }
    
}

void Admin::AddClass(){
    cout<<"-----输入课程名-----"<<endl;
    string newClassName;
    cin>>newClassName;
    DB database;
    sprintf(database.mquery, "SELECT * FROM score WHERE classname='%s'", newClassName.c_str());
    mysql_query(database.conn, database.mquery);
    database.res = mysql_use_result(database.conn);
    database.row = mysql_fetch_row(database.res);
    if (database.row) {
        cout<<"课程已存在！\n"<<endl;
        return;
    }
    DB studb;
    sprintf(studb.mquery, "SELECT id FROM users WHERE usertype!=1&&usertype!=4");

    mysql_query(studb.conn, studb.mquery);
    studb.res = mysql_use_result(studb.conn);

    while((studb.row = mysql_fetch_row(studb.res))) {
        sprintf(database.mquery, "INSERT INTO score (classname, stuid) VALUES ('%s', '%s');", newClassName.c_str(), *studb.row);
        mysql_query(database.conn, database.mquery);
        if (mysql_errno(database.conn)) {
            cout<<"操作失败"<<endl;
            cout<<"INSERT error: #"<<mysql_errno(database.conn)<<" "<<mysql_error(database.conn)<<endl;
            return;
        }
    }
    cout<<"操作成功"<<endl;
}

void Admin::DelClass(){//删除课程
    cout<<"-----输入课程名-----"<<endl;
    string delClassName;
    cin>>delClassName;
    DB database;
    sprintf(database.mquery, "DELETE FROM score WHERE classname='%s'", delClassName.c_str());
    mysql_query(database.conn, database.mquery);
    if (!mysql_errno(database.conn)) {
        cout<<"操作成功"<<endl;
    } else {
        cout<<"操作失败"<<endl;
        cout<<"Delete error: #"<<mysql_errno(database.conn)<<" "<<mysql_error(database.conn)<<endl;
    }
}


void Admin::ChaUser(string number){
    User newUser(number);
    newUser.showInfo();
    cout<<"-----请输入修改的信息-----"<<endl;
    
    cout<<"1.姓名\n2.学号(工号)\n3.密码\n4.成绩\n其余按键退出"<<endl;
    int xuanze;
    cin>>xuanze;
    
    switch (xuanze) {
        case 1:{
            cout<<"请输入新的姓名："<<endl;
            string newName;
            cin>>newName;
            
            newUser.cSName(newName);
        }
            
            break;
            
            
        case 2:{
            cout<<"请输入新的学号(工号）："<<endl;
            string newNo;
            cin>>newNo;
            
            newUser.cStudentNo(newNo);
        }
            break;
            
        case 3:{
            cout<<"请输入新的密码："<<endl;
            string newPa;
            cin>>newPa;
            
            newUser.cSPassword(newPa);
        }
            break;
            
        case 4:{
            cout<<"请输入课程："<<endl;
            string chClass;
            cin>>chClass;
            cout<<"请输入成绩："<<endl;
            int chScore;
            cin>>chScore;
            
            newUser.cSScore(chClass, chScore);
            
        }
            break;
        default:
            break;
    }
}


void Admin::ShowAllScore(string shClass){//显示所有学生某门课程的成绩
    DB database;
    sprintf(database.mquery, "SELECT * FROM score WHERE classname='%s'", shClass.c_str());
    mysql_query(database.conn, database.mquery);
    database.res = mysql_use_result(database.conn);
    database.row = mysql_fetch_row(database.res);
    if (!database.row) {
        cout<<"课程不存在！"<<endl;
    } else {
        string tmpscore;
        tmpscore = database.row[2];
        if (!tmpscore.compare("-1")) {
            cout<<database.row[1]<<":   "<<"未登记！"<<endl;
        } else {
            cout<<database.row[1]<<":   "<<database.row[2]<<endl;
        }
        while((database.row = mysql_fetch_row(database.res))) {
            tmpscore = database.row[2];
            if (!tmpscore.compare("-1")) {
                cout<<database.row[1]<<":   "<<"未登记！"<<endl;
            } else {
                cout<<database.row[1]<<":   "<<database.row[2]<<endl;
            }
        }
    }
    cout<<endl;
}


string Admin::SearchUser(){ //查询学生,返回学号; 跳过老师，只查学生
    string searchNumber;
    bool chonghe = false; //查询到的是否重合
    
    cout<<"----用户检索系统----"<<endl;
    cout<<"1.按学号\n2.按姓名\n3.按课程成绩"<<endl;
    int xuanze;
    cin>>xuanze;
    switch (xuanze) {
        case 1:{
            cout<<"-----请输入学生ID-----"<<endl;
            string TmpUserNo;
            cin>>TmpUserNo;
            DB database;
            sprintf(database.mquery, "SELECT id,name FROM users WHERE id='%s'", TmpUserNo.c_str());
            mysql_query(database.conn, database.mquery);
            database.res = mysql_use_result(database.conn);
            if (database.res) {
                database.row = mysql_fetch_row(database.res);
                if (database.row) {
                    cout<<"学生ID:  "<<database.row[0]<<endl;
                    cout<<"学生姓名: "<<database.row[1]<<endl;
                    cout<<"------\n";
                    searchNumber = TmpUserNo;
                } else {
                    cout<<"------用户不存在------\n"<<endl;
                    searchNumber = "不存在";
                }
            }
            //查询学号，然后打印学号和姓名,赋值searchNumber不存在的话打印不存在
            //searchNumber="不存在";
        }
            
            break;
            
        case 2:{
            cout<<"-----请输入学生姓名-----"<<endl;
            string TmpUserName;
            cin>>TmpUserName;
            DB database;
            sprintf(database.mquery, "SELECT id,name FROM users WHERE name='%s'", TmpUserName.c_str());
            mysql_query(database.conn, database.mquery);
            database.res = mysql_use_result(database.conn);
            if (database.res) {
                database.row = mysql_fetch_row(database.res);
                if (database.row) {
                    cout<<"学生ID:  "<<database.row[0]<<endl;
                    cout<<"学生姓名: "<<database.row[1]<<endl;
                    cout<<"------\n";
                    searchNumber = database.row[0];
                    while((database.row = mysql_fetch_row(database.res))) {
                        cout<<"学生ID:  "<<database.row[0]<<endl;
                        cout<<"学生姓名: "<<database.row[1]<<endl;
                        cout<<"------\n";
                        chonghe=true;
                    }
                } else {
                    cout<<"------用户不存在------\n"<<endl;
                    searchNumber = "不存在";
                }
            }
        }
        
            break;
        
        case 3:{
            cout<<"-----请输入课程名称-----"<<endl;
            string TmpClassName;
            cin>>TmpClassName;
            cout<<"----请输入成绩表达式----"<<endl;
            cout<<"格式为：score [=,>,<,>=,<=] [分数]\n连接符：[and,or]"<<endl;
            cout<<"例如： score>60 and score<90"<<endl;
            string TmpStr;
            cin.get();
            getline(cin,TmpStr);
            DB database;
            sprintf(database.mquery, "SELECT stuid,score FROM score WHERE classname='%s' AND score>=0 AND(%s)", TmpClassName.c_str(), TmpStr.c_str());
            mysql_query(database.conn, database.mquery);
            if (mysql_errno(database.conn)) {
                cout<<"操作失败，请检查表达式语法"<<endl;
                cout<<"SELECT error: #"<<mysql_errno(database.conn)<<" "<<mysql_error(database.conn)<<endl;
                return "不存在";
            }
            database.res = mysql_use_result(database.conn);
            if (database.res) {
                database.row = mysql_fetch_row(database.res);
                if (database.row) {
                    cout<<"学生ID:  "<<database.row[0]<<endl;
                    cout<<"学生成绩: "<<database.row[1]<<endl;
                    cout<<"------\n";
                    searchNumber = database.row[0];
                    while((database.row = mysql_fetch_row(database.res))) {
                        cout<<"学生ID:  "<<database.row[0]<<endl;
                        cout<<"学生成绩: "<<database.row[1]<<endl;
                        cout<<"------\n";
                        chonghe=true;
                    }
                } else {
                    cout<<"------用户不存在------\n"<<endl;
                    searchNumber = "不存在";
                }
            }
        }
            break;
            
        default:
            break;
    }
    
    if(chonghe==true){
        cout<<"----请输入准确的学号-----"<<endl;
        string TmpUserNo;
        cin>>TmpUserNo;
        DB database;
        sprintf(database.mquery, "SELECT id,name FROM users WHERE id='%s'", TmpUserNo.c_str());
        mysql_query(database.conn, database.mquery);
        database.res = mysql_use_result(database.conn);
        if (database.res) {
            database.row = mysql_fetch_row(database.res);
            if (database.row) {
                cout<<"学生ID:  "<<database.row[0]<<endl;
                cout<<"学生姓名: "<<database.row[1]<<endl;
                searchNumber = TmpUserNo;
            } else {
                cout<<"------用户不存在------\n"<<endl;
                searchNumber = "不存在";
            }
        }
        //查询学号，然后打印学号和姓名,赋值searchNumber不存在的话打印不存在
        //searchNumber="不存在";
        
    }
    
    return searchNumber;
}





