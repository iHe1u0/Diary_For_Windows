#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>

class DiaryRecord {
public:
	int id = 0;
	std::string text = "";
};

class DBHelper {
public:
	DBHelper(const std::string name);
	~DBHelper();
	/**
	 * @brief Get status code of current database
	 *
	 * @return int Status code
	 */
	int getDBStatusCode() const;
	/**
	 * @brief Get status of current database
	 *
	 * @return std::string database status message
	 */
	std::string getDBStatusMsg() const;
	/**
	 * @brief Execute sql
	 *
	 * @param command sql
	 * @return int result
	 */
	int execute(const std::string command) const;
	/**
	 * @brief Get the All Lists object
	 *
	 * @return std::vector<DiaryRecord>
	 */
	std::vector<DiaryRecord> getAllLists() const;

private:
	std::string dbName;
	sqlite3* db = nullptr;
	mutable int dbStatus = 0;
	mutable std::string errorMsg = "no error";
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};
