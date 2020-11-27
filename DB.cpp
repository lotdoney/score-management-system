//
//  DB.cpp
//  helloworld
//
//  Created by 张清源 on 2020/11/25.
//

#include "DB.h"

DB::DB() {
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, "localhost", "root", "3802380", "xscjglxt", 0, NULL, 0)) {
        cout<<"数据库连接失败！"<<endl;
    }
    res = nullptr;
    row = nullptr;
    mquery = new char[500];
}

DB::~DB() {
    mysql_close(conn);
    delete [] mquery;
    if (res) {
       // delete res;
    }
    if (row) {
      //  delete row;
    }
}
