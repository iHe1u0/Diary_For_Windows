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

//
//int Callback(void* value, int argc, char** argv, char** azColName) {
//	std::vector<DiaryRecord> vRecord;
//	for (size_t index = 0; index < argc; index++) {
//		auto key = std::string(azColName[index]);
//		auto value = argv[index] ? argv[index] : "";
//		vRecord.push_back(DiaryRecord(std::stoi(key), value));
//		std::cout << std::format("[{0}:{1}]\n", key, value);
//	}
//	return 0;
//}

void DBHelper::insert(const std::string& tableName, const DiaryRecord& record) const
{
	sqlite3_stmt* stmt;
	auto sql = std::format("insert into {0} values (?,?)", tableName);
	if (sqlite3_prepare(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
	{
		//if (sqlite3_bind_int(stmt, 1, record.id) != SQLITE_OK) {
		//	llmsg("\nCould not bind int.\n");
		//	return;
		//}
		if (sqlite3_bind_text(stmt, 2, record.text.c_str(), record.text.length(), SQLITE_STATIC) != SQLITE_OK) {
			llmsg("\nCould not bind int.\n");
			return;
		}

		if (sqlite3_step(stmt) != SQLITE_DONE) {
			llmsg("\nCould not step (execute) stmt.\n");
		}
	}
	sqlite3_finalize(stmt);
}

std::vector<DiaryRecord> DBHelper::getAllLists(std::string tableName) const
{
	std::vector<DiaryRecord> vRecord;
	auto sql = std::format("select * from {0};", tableName);
	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int id = sqlite3_column_int(stmt, 0);
			auto data = sqlite3_column_text(stmt, 1);
			std::string strData(reinterpret_cast<const char*>(data));
			vRecord.push_back(DiaryRecord(id, strData));
		}
	}
	if (dbStatus != SQLITE_DONE) {
		vRecord.push_back(DiaryRecord(0, "Failed to SQLITE_DONE: "));
		vRecord.push_back(DiaryRecord(1, sqlite3_errmsg(db)));
	}
	sqlite3_finalize(stmt);
	return vRecord;
}

void DBHelper::update(const std::string& tableName, const DiaryRecord& record) const
{
	sqlite3_stmt* stmt;
	auto updateSQL = std::format("update {0} SET data = ? WHERE id = ?;", tableName);
	if ((sqlite3_prepare_v2(db, updateSQL.c_str(), -1, &stmt, nullptr)) == SQLITE_OK)
	{
		if (sqlite3_bind_text(stmt, 1, record.text.c_str(), record.text.length(), SQLITE_STATIC) != SQLITE_OK) {
			llmsg("\nCould not bind data.\n");
			return;
		}
		if (sqlite3_bind_int(stmt, 2, record.id) != SQLITE_OK) {
			llmsg("\nCould not bind id.\n");
			return;
		}
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
}

void DBHelper::deleteById(const std::string& tableName, int id)
{
	auto deleteSQL = std::format("DELETE FROM {0} WHERE id = ?;", tableName);
	sqlite3_stmt* deleteStmt;
	if (sqlite3_prepare_v2(db, deleteSQL.c_str(), -1, &deleteStmt, nullptr) == SQLITE_OK) {
		if (sqlite3_bind_int(deleteStmt, 1, id) == SQLITE_OK)
		{
			sqlite3_step(deleteStmt);
		}
	}
	sqlite3_finalize(deleteStmt);
}

int DBHelper::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (size_t index = 0; index < argc; index++) {
		auto key = std::string(azColName[index]);
		auto value = argv[index] ? argv[index] : "";
		// std::cout << std::format("[{0}:{1}]\n", key, value);
	}
	return 0;
}