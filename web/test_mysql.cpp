#include <iostream>
#include <mysql/mysql.h>

using namespace std;

int main() {
    MYSQL* conn; // 创建MYSQL对象
    MYSQL_RES* res; // 创建MYSQL_RES对象
    MYSQL_ROW row; // 创建MYSQL_ROW对象

    conn = mysql_init(NULL); // 初始化MYSQL对象
    if (!conn) {
        cout << "MySQL initialization failed!" << endl;
        return 1;
    }

    conn = mysql_real_connect(conn, "localhost", "zhang", "zhang123", "simple", 0, NULL, 0); // 连接MYSQL数据库
    if (conn) {
        cout << "Connection successful!" << endl;
        mysql_query(conn, "SELECT * FROM user"); // 查询MYSQL数据库
        res = mysql_use_result(conn); // 获取MYSQL_RES对象
        while ((row = mysql_fetch_row(res)) != NULL) { // 遍历MYSQL_RES对象
            cout << row[0] << " " << row[1] << " " << row[2] << endl; // 输出MYSQL_ROW对象
        }
        mysql_free_result(res); // 释放MYSQL_RES对象
        mysql_close(conn); // 关闭MYSQL连接
    }
    else {
        cout << "Connection failed!" << endl;
        return 1;
    }

    return 0;
}
