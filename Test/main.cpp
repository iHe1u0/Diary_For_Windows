#include <iostream>
#include <string>
#include <memory>
extern "C"
{
#include <sqlite3.h>
}
#include "db_helper.h"

template <typename T>
inline void llmsg(const T &t)
{
    std::cout << t << std::endl;
}

int main()
{
    llmsg("sqlite3 version: " + std::string(sqlite3_version));
    auto dbHelper = std::make_shared<DBHelper>("data.db");
    auto sql = "CREATE TABLE COMPANY("
               "ID INT PRIMARY KEY     NOT NULL,"
               "NAME           TEXT    NOT NULL,"
               "AGE            INT     NOT NULL,"
               "ADDRESS        CHAR(50),"
               "SALARY         REAL );";
    dbHelper->execute(sql);
    llmsg(dbHelper->getDBStatusMsg());
    return 0;
}
