#pragma once
#include <sqlite3.h>
#include <string>

class DBHelper
{
public:
    DBHelper(const std::string name);
    ~DBHelper();
    /**
     * 获取数据库当前的状态
     */
    int getDBStatusCode() const;
    /**
     * 获取数据库当前的状态
     */
    std::string getDBStatusMsg() const;
    /**
     * 执行语句
     */
    int execute(const std::string command) const;

private:
    std::string dbName;
    sqlite3 *db;
    mutable int dbStatus;
    mutable std::string errorMsg = "no error";
    /**
     * 回调函数
     */
    static int DBHelper::callback(void *NotUsed, int argc, char **argv, char **azColName);
};
