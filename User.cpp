//
//  User.cpp
//  helloworld
//
//  Created by 张清源 on 2020/11/25.
//

#include "User.h"

User::User(string newNo){
    setUser(newNo);
}

User::~User(){
    Score *tmpscore;
    Score *headscore;
    if (sscore != nullptr) {
        if (sscore->next != sscore->head) {
            headscore = sscore;
            sscore = sscore->next;
            while (sscore->next != sscore->head) {
                tmpscore = sscore;
                sscore = sscore->next;
                delete tmpscore;
            }
            delete sscore;
            delete headscore;
        } else {
            delete sscore;
        }
        
    }
}

void User::setUser(string newNo){
    StudentNo = newNo;
    sscore = nullptr;
    sstail = nullptr;
    DB database;
    sprintf(database.mquery, "SELECT * FROM users WHERE id='%s'", StudentNo.c_str());
    mysql_query(database.conn, database.mquery);
    database.res = mysql_use_result(database.conn);
    if (database.res) {
        database.row = mysql_fetch_row(database.res);
        if (database.row) {
            sname = database.row[1];
            UserType = atoi(database.row[2]);
            spassword = database.row[3];
        } else {
            cout<<"用户不存在！"<<endl;
            UserType = 0;
            return;
        }
    }
    mysql_free_result(database.res);
    sprintf(database.mquery, "SELECT * FROM score WHERE stuid='%s'", StudentNo.c_str());
    mysql_query(database.conn, database.mquery);
    database.res = mysql_use_result(database.conn);
    int headflag = 1;
    if(database.res) {
        while((database.row = mysql_fetch_row(database.res))) {
            Score *tmpscore;
            tmpscore = new Score(StudentNo, database.row[0], atoi(database.row[2]));
            if (headflag) {
                tmpscore->head = tmpscore;
                tmpscore->next = tmpscore;
                sscore = tmpscore;
                sstail = tmpscore;
                headflag = 0;
            } else {
                tmpscore->head = sscore;
                tmpscore->next = sscore;
                sstail->next = tmpscore;
                sstail = tmpscore;
            }
        }
    }
}

int User::getUserType() const {
    if(UserType>=1&&UserType<=4)
        return UserType;
    
    else{
        cout<<"未初始化用户，类型错误或用户类型未定！"<<endl;
        return 0;
    }
}





string User::getStudentNo() const{
    if (StudentNo=="暂无") {
        cout<<"未初始化用户，学号错误，可能已被删除！"<<endl;
        return "NULL";
    }
    else
        return StudentNo;
}

string User::getName() const{
    if (sname=="暂无") {
        cout<<"未初始化用户，姓名错误，可能已被删除！"<<endl;
        return "NULL";
    }
    else
        return sname;
}

string User::getPassword() const{
    if (spassword=="暂无") {
        cout<<"未初始化用户，密码错误！"<<endl;
        return "NULL";
    }
    else
        return spassword;
}
Score* User::getScore() const{
    if (sscore==NULL) {
        cout<<"未初始化用户,分数错误！"<<endl;
        return NULL;
    }
    else
        return sscore;
}

void User::showInfo(){
    cout<<"---欢迎进入学生成绩管理系统----"<<endl;
    cout<<sname<<"同学你好！以下是您的学生成绩信息"<<endl;
    cout<<"学号："<<StudentNo<<endl;
    cout<<"各科成绩："<<endl;

    if (sscore == NULL) {
        cout<<"无成绩记录"<<endl;
        return;
    } else {
        int tmpScore;
        if (sscore->next != sscore->head) {
            do{
                tmpScore = sscore->getScore();
                if (tmpScore == -1) {
                    cout<<sscore->ClassName<<"：  "<<"未登记"<<endl;
                } else {
                    cout<<sscore->ClassName<<"：  "<<tmpScore<<endl;
                }
                sscore = sscore->next;
            } while (sscore->next!=sscore->head);
        } else {
            tmpScore = sscore->getScore();
            if (tmpScore == -1) {
                cout<<sscore->ClassName<<"：  "<<"未登记"<<endl;
            } else {
                cout<<sscore->ClassName<<"：  "<<tmpScore<<endl;
            }
        }
        sscore=sscore->head;
    }
    cout<<"---------------------------"<<endl;
}

void User::cStudentNo(string newNo){
    DB database;
    sprintf(database.mquery, "UPDATE users SET id='%s' WHERE id='%s';", newNo.c_str(), StudentNo.c_str());
    mysql_query(database.conn, database.mquery);
    if (!mysql_errno(database.conn)) {
        cout<<"操作成功"<<endl;
    } else {
        cout<<"操作失败"<<endl;
        cout<<"UPDATE error: #"<<mysql_errno(database.conn)<<" "<<mysql_error(database.conn)<<endl;
    }
}

void User::cSName(string newName)
{
    DB database;
    sprintf(database.mquery, "UPDATE users SET name='%s' WHERE id='%s';", newName.c_str(), StudentNo.c_str());
    mysql_query(database.conn, database.mquery);
    if (!mysql_errno(database.conn)) {
        cout<<"操作成功"<<endl;
    } else {
        cout<<"操作失败"<<endl;
        cout<<"UPDATE error: #"<<mysql_errno(database.conn)<<" "<<mysql_error(database.conn)<<endl;
    }
}
void User::cSPassword(string newPass){
    DB database;
    sprintf(database.mquery, "UPDATE users SET password='%s' WHERE id='%s';", newPass.c_str(), StudentNo.c_str());
    mysql_query(database.conn, database.mquery);
    if (!mysql_errno(database.conn)) {
        cout<<"操作成功"<<endl;
    } else {
        cout<<"操作失败"<<endl;
        cout<<"UPDATE error: #"<<mysql_errno(database.conn)<<" "<<mysql_error(database.conn)<<endl;
    }
}
void User::cSScore(string className,int newScore){
    if (sscore == nullptr) {
        cout<<sname<<"没有该课程："<<className<<endl;
        return;
    }
    int change_flag=0; //标记修改是否成功
    if (sscore->next != sscore->head) {
        do{
            if(className==sscore->ClassName){
                sscore->changeScore(newScore);
                change_flag=1;
            }
            sscore = sscore->next;
        } while (sscore->next!=sscore->head);
        if(className==sscore->ClassName){
            sscore->changeScore(newScore);
            change_flag=1;
        }
    } else {
        if(className==sscore->ClassName){
            sscore->changeScore(newScore);
            change_flag=1;
        }
    }
    sscore = sscore->head;
    
    if(change_flag==0){
        cout<<sname<<"没有该课程："<<className<<endl;
    }
    
}
