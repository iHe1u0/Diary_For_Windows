#include "db_helper.h"

DBHelper::DBHelper(const std::string name)
{
    dbName = name;
    dbStatus = sqlite3_open(dbName.c_str(), &db);
}

DBHelper::~DBHelper()
{
    if (db)
    {
        sqlite3_close(db);
    }
}

int DBHelper::getDBStatusCode() const
{
    return dbStatus;
}

std::string DBHelper::getDBStatusMsg() const
{
    return errorMsg;
}

int DBHelper::execute(const std::string sql) const
{
    char *msg = 0;
    dbStatus = sqlite3_exec(db, sql.c_str(), callback, 0, &msg);
    errorMsg = std::string(msg);
    return dbStatus;
}

int DBHelper::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}