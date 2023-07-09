#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>

#define llmsg(msg) \
std::cout<< __FILE__ << "@" << __LINE__ << ":" << msg <<std::endl

class DiaryRecord {
public:
	DiaryRecord() = default;
	DiaryRecord(int id, const std::string& data) {
		this->id = id;
		this->text = data;
	}
	DiaryRecord(std::string id, const std::string& data) :DiaryRecord(std::stoi(id), data) {};
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
	* @brief Insert data
	* 
	*/
	void insert(const std::string& tableName, const DiaryRecord& record) const;
	/**
	 * @brief Get the All Lists object
	 *
	 * @return std::vector<DiaryRecord>
	 */
	std::vector<DiaryRecord> getAllLists(std::string tableName) const;
	/**
	* @breif Update data by id
	*/
	void update(const std::string& tableName, const DiaryRecord& record)const;

	void deleteById(const std::string& tableName, int id);

private:
	std::string dbName;
	sqlite3* db = nullptr;
	mutable int dbStatus = 0;
	mutable std::string errorMsg = "no error";
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};
