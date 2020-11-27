//
//  Score.cpp
//  helloworld
//
//  Created by 张清源 on 2020/11/25.
//


#include "Score.h"

Score::Score(string StdentNO, string ClassName){
    this->StdentNO = StdentNO;
    this->ClassName = ClassName;
    this->next = nullptr;
    this->head = nullptr;
    DB database;
    sprintf(database.mquery, "SELECT score FROM users WHERE stuid='%s' and classid='%s'", StdentNO.c_str(), ClassName.c_str());
    mysql_query(database.conn, database.mquery);
    database.res = mysql_use_result(database.conn);
    if(database.res) {
        database.row = mysql_fetch_row(database.res);
        if (database.row) {
            this->score = atoi(*database.row);
        } else {
            cout<<"学生无此课"<<endl;
        }
    }
}

Score::Score(string StdentNO, string ClassName, int score){
    this->next = nullptr;
    this->head = nullptr;
    this->StdentNO = StdentNO;
    this->ClassName = ClassName;
    this->score = score;
}

int Score::getScore(){
    return score;
}

//int Score::getTuition(){
//
//}

void Score::changeScore(int newScore){
    if((newScore>100||newScore<0)&&(newScore!=-1))
        cout<<"输入成绩有误！！"<<endl;
    else{
        score = newScore;
        DB database;
        sprintf(database.mquery, "SELECT * FROM score WHERE classname='%s'", ClassName.c_str());
        mysql_query(database.conn, database.mquery);
        database.res = mysql_use_result(database.conn);
        if (database.res) {
            database.row = mysql_fetch_row(database.res);
            if (database.row) {
                DB updatedb;
                sprintf(updatedb.mquery, "UPDATE score SET score=%d WHERE classname='%s' AND stuid=%s;", newScore, ClassName.c_str(), StdentNO.c_str());
                mysql_query(updatedb.conn, updatedb.mquery);
                if (!mysql_errno(updatedb.conn)) {
                    cout<<"操作成功"<<endl;
                } else {
                    cout<<"操作失败"<<endl;
                    cout<<"UPDATE error: #"<<mysql_errno(updatedb.conn)<<" "<<mysql_error(updatedb.conn)<<endl;
                }
            } else {
            cout<<"数据库中不存在该课程，请先添加"<<endl;
            }
        }
    }
    
}//根据输入课程和分数修改成绩
