#pragma once

#include <winsock.h>
#include <mysql.h>
#pragma comment(lib,"libmySQL.lib")  //要加不然会编译出错
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class MyDataBase
{
private:
	MYSQL* sql = nullptr;
	MYSQL_RES* res = nullptr;
	MYSQL_ROW row = nullptr;
	bool connect_flag;
	void showres();
public:
	MyDataBase();
	MyDataBase(MYSQL* mysql);
	~MyDataBase();
	void connect(const string& host, const string& user, const string& password,
		const string& database = "mysql", unsigned int port = 0,
		const char* unix_socket = nullptr, unsigned long client_flag = 0);
	void disconnect();
	void show_database();
	void create_database(const string& database);
	void use_database(const string& database);
	void delete_database(const string& database);
	void show_table();
	void create_table(const string& table, const string& elements);
	vector<vector<string>> selectitem(const string& table, const string& value);
	vector<vector<string>> selectitem(const string& table, const string& value, const string& limits);
	void insert_table(const string& table, const string& value);
	void insert_table(const string& table, const string& value, const string& col);
	void delete_table(const string& table, const string& value);
	void delete_table(const string& table);
	void update_table(const string& table, const string& value, const string& limits);
	void Alter_table(const string& table, const string& op, const string& name_type);
	void query(const string& limits, const string& command);
};