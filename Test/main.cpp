#include <format>
#include <iostream>
#include <memory>
#include <string>
extern "C" {
#include <sqlite3.h>
}
#include "db_helper.h"

void createTable(auto dbHelper, auto tableName) {
	auto createTableSql = std::format(
		"create table {}("
		"`id` integer primary key autoincrement,"
		"`data` text );",
		tableName);
	dbHelper->execute(createTableSql);
}

void insertData(const std::shared_ptr<DBHelper> dbHelper, auto tableName, DiaryRecord record) {
	dbHelper->insert(tableName, record);
}

std::vector<DiaryRecord> queryData(auto dbHelper, auto tableName) {
	std::vector<DiaryRecord> vRecords = dbHelper->getAllLists(tableName);
	for (DiaryRecord r : vRecords)
	{
		llmsg(r.text);
	}
	return vRecords;
}

int main(int argc, char** argv) {

	for (size_t i = 0; i < argc; i++)
	{
		llmsg(argv[i]);
	}
	// llmsg("sqlite3 version: " + std::string(sqlite3_version));
	auto dbHelper = std::make_shared<DBHelper>("data.db");
	auto tableName = "book";

	createTable(dbHelper, tableName);

	//if (argv[1])
	//{
	//	insertData(dbHelper, tableName, DiaryRecord(0, argv[1]));
	//}
	insertData(dbHelper, tableName, DiaryRecord(0, "你好呀，亲爱的小白现在是夏天呢"));

	dbHelper->update(tableName, DiaryRecord(1, "你好111"));

	queryData(dbHelper, tableName);

	return 0;
}
