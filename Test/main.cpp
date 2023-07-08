#include <format>
#include <iostream>
#include <memory>
#include <string>
extern "C" {
#include <sqlite3.h>
}
#include "db_helper.h"

template <typename T>
inline void llmsg(const T& t) {
	std::cout << t << std::endl;
}

int main() {
	// llmsg("sqlite3 version: " + std::string(sqlite3_version));
	auto dbHelper = std::make_shared<DBHelper>("data.db");
	auto tableName = "book";

	auto createTableSql = std::format(
		"create table {}("
		"`id` int primary key not null,"
		"`data` text );",
		tableName);
	// dbHelper->execute(createTableSql);

	// auto insertRecord = std::format("insert into {0} values({1},'{2}');", tableName, 2, "Hello");
	// dbHelper->execute(insertRecord);

	auto queryRecord = std::format("select id from {0};", tableName);
	dbHelper->execute(queryRecord);

	//std::vector<DiaryRecord> result = dbHelper->getAllLists();



	return 0;
}
