//
//  DB.h
//  helloworld
//
//  Created by 张清源 on 2020/11/25.
//

#ifndef DB_h
#define DB_h
#include <iostream>
#include "mysql.h"

using namespace std;

class DB{
    friend class User;
    friend class Score;
    friend class Admin;
    
public:
    MYSQL *conn;
    MYSQL_RES  *res;
    MYSQL_ROW  row;
    MYSQL_FIELD col;
    char *mquery;

    DB();
    ~DB();
    
};


#endif /* DB_h */
