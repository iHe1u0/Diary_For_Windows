#include "db_helper.h"
#include <iostream>
#include <list>
#include <string>
#include <format>

DBHelper::DBHelper(const std::string name) {
	dbName = name;
	dbStatus = sqlite3_open(dbName.c_str(), &db);
}

DBHelper::~DBHelper() {
	if (db) {
		sqlite3_close(db);
	}
}

int DBHelper::getDBStatusCode() const {
	return dbStatus;
}

std::string DBHelper::getDBStatusMsg() const {
	return errorMsg;
}

int DBHelper::execute(const std::string sql) const {
	char* msg = 0;
	dbStatus = sqlite3_exec(db, sql.c_str(), &callback, 0, &msg);
	if (msg)
	{
		errorMsg = std::string(msg);
	}
	return dbStatus;
}

std::vector<DiaryRecord> DBHelper::getAllLists() const
{
	return std::vector<DiaryRecord>();
}

int DBHelper::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (size_t index = 0; index < argc; index++) {
		auto key = std::string(azColName[index]);
		auto value = argv[index] ? argv[index] : "";
		std::cout << std::format("[{0}:{1}]\n", key, value);
	}
	return 0;
}