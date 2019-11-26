#include "connect_database.h"
#include<string>
#include<iostream>
using namespace std;

void MyDataBase::disconnect() {    //断开连接
	if (sql)
		mysql_close(sql);
	sql = nullptr;
	res = nullptr;
	connect_flag = false;
	cout << "disconnect success!" << endl;
}

MyDataBase::MyDataBase() {          //初始化
	sql = mysql_init(nullptr);
	if (!sql)
		cout << "init error!" << endl;
	connect_flag = false;
}

MyDataBase::MyDataBase(MYSQL* mysql) {      //初始化，构造函数的重载
	sql = mysql_init(mysql);
	if (!sql)
		cout << "init error!" << endl; 
	connect_flag = false;
}

MyDataBase::~MyDataBase() {
	if (connect_flag)
		disconnect();
	sql = nullptr;
	mysql_free_result(res);
	res = nullptr;
}

void MyDataBase::connect(const string& host, const string& user, const string& password, const string& database,
	unsigned int port, const char* unix_socket, unsigned long client_flag) {
	if (!sql) {
		cout << "sql has not been initialized!" << endl;          //判断是否初始化
		return;
	}
	if (!mysql_real_connect(sql, host.c_str(), user.c_str(), password.c_str(), database.c_str(),     //进行连接
		port, unix_socket, client_flag)) {
		cout << "connect error!" << endl;
		return;

	}
	cout << "connect success!" << endl;
}
void MyDataBase::show_database()               //查看数据库
{
	string str = "show databases";
	if (mysql_query(sql, str.c_str())) {
		cout << "show databases error!" << endl;
		return;
	}
	showres();
}

void MyDataBase::create_database(const string& database) {                     //传入的名字作为被创建新的数据库名
	string str = "create database if not exists " + database;
	if (mysql_query(sql, str.c_str())) {
		cout << "create database error!" << endl;
		return;
	}
	cout << "create database success!" << endl;
}

void MyDataBase::use_database(const string& database) {                        //调用数据库
	string str = "use " + database;
	if (mysql_query(sql, str.c_str())) {
		cout << "use database error!" << endl;
		return;
	}
	cout << "use " << database << " now!" << endl;
}

void MyDataBase::delete_database(const string& database) {                    //删除数据库，一般不用
	string str = "drop database " + database;
	if (mysql_query(sql, str.c_str())) {
		cout << "delete database error!" << endl;
		return;
	}
	cout << database << " has been deleted!" << endl;
}

void MyDataBase::show_table() {                                            //查看表
	string str = "show tables";
	if (mysql_query(sql, str.c_str())) {
		cout << "show tables error!" << endl;
		return;
	}
	showres();
}

void MyDataBase::create_table(const string& table, const string& elements) {       //创造表，1、表名   2、成员，成员格式为     列名 类型，列名 类型，..... 
	string str = "create table " + table + "(" + elements + ")";
	if (mysql_query(sql, str.c_str())) {
		cerr << "create table error!" << endl;
		return;
	}
	cout << "create table success!" << endl;
}

vector<vector<string>> MyDataBase::selectitem(const string& table, const string& value)  
{
	string str = "select " + value + " from " + table;//查询表的数据，  1、表名     2、字段名 ，多段用逗号隔开

	cout << str << endl;
	if (mysql_query(sql, str.c_str())) 
	{
		cout << "select error!" << endl;
		return {};
	}

	vector<vector<string>> ret;
	res = mysql_use_result(sql);//mysql_use_result() 初始化一个一行一行地结果集合的检索。
	while ((row = mysql_fetch_row(res)) != nullptr) 
	{
		int i = 0;
		vector<string> temp;
		while (i < mysql_num_fields(res))
			temp.push_back(row[i++]);
		ret.push_back(temp);
	}
	mysql_free_result(res);
	res = nullptr;
	return ret;
}

vector<vector<string>> MyDataBase::selectitem(const string& table, const string& value, const string& limits) {
	string str = "select " + value + " from " + table + " where " + limits;
	cout << str << endl;
	if (mysql_query(sql, str.c_str())) {
		cout << "select error!" << endl;
		return {};
	}

	vector<vector<string>> ret;
	res = mysql_use_result(sql);
	while ((row = mysql_fetch_row(res)) != nullptr) {
		int i = 0;
		vector<string> temp;
		while (i < mysql_num_fields(res))
			temp.push_back(row[i++]);
		ret.push_back(temp);
	}
	mysql_free_result(res);
	res = nullptr;
	return ret;
}

void MyDataBase::showres() {
	res = mysql_use_result(sql);
	cout << "****************The result is:****************" << endl;
	while ((row = mysql_fetch_row(res)) != nullptr) {
		int i = 0;
		while (i < mysql_num_fields(res))
			cout << row[i++] << "\t";
		cout << endl;
	}
	cout << "**********************************************" << endl;
	mysql_free_result(res);
	res = nullptr;//展示结果
}

void MyDataBase::insert_table(const string& table, const string& value) {  //插入， 1、表名     2、数据格式   data1,data2,data3......
	string str = "insert into " + table + " values (" + value + ")";
	cout << str << endl;
	if (mysql_query(sql, str.c_str())) {
		cout << "insert error!" << endl;
		return;
	}
	cout << "insert success!" << endl;
}

void MyDataBase::insert_table(const string& table, const string& value, const string& col) {//插入，1、表名  2、数据 data1,data2,data3.....  3、列名  格式同data
	string str = "insert into " + table + " (" + col + ") values (" + value + ")";
	cout << str << endl;
	if (mysql_query(sql, str.c_str())) {
		cout << "insert error!" << endl;
		return;
	}
	cout << "insert success!" << endl;
}


void MyDataBase::delete_table(const string& table, const string& value) {
	string str = "delete from " + table + " where " + value;
	cout << str << endl;
	if (mysql_query(sql, str.c_str())) {
		cout << "delete error!" << endl;
		return;
	}
	cout << "delete success!" << endl;
}
void MyDataBase::delete_table(const string& table) {
	string str = "drop table " + table;
	cout << str << endl;
	if (mysql_query(sql, str.c_str())) {
		cout << "delete error!" << endl;
		return;
	}
	cout << "delete success!" << endl;
}

void MyDataBase::update_table(const string& table, const string& value, const string& limits) {
	string str = "update " + table + " set " + value + " where " + limits;
	cout << str << endl;
	if (mysql_query(sql, str.c_str())) {
		cout << "delete error!" << endl;
		return;
	}
	cout << "update success!" << endl;
}

void MyDataBase::Alter_table(const string& table, const string& op,const string& name_type) {      //1、表名 2、操作 add/drop/modify/change  3、列名 列类型
	string str = "alter table " + table + " "+ op +" column " + "name_type";
	cout << str << endl;
	if (mysql_query(sql, str.c_str())) {
		cout << "modify error!" << endl;
		return;
	}
	cout << "modify success!" << endl;
}


void MyDataBase::query(const string& limits,const string& command) {
	string str = "select " + limits + " from " + command;
	if (mysql_query(sql, str.c_str())) {      //mysql_query()：向数据库发送查询语句,第一个参数为MYSQL变量的地址，第二个参数为"查询语句"
		cout << "query error!" << endl;
		return;
	}
	cout << "query success!" << endl;
}
void Process_database()
{
	MyDataBase mdb;
	mdb.connect("localhost", "root", "change");
	mdb.create_database("BSDL_DATA");
	mdb.use_database("BSDL_DATA");
	mdb.create_table("tst", "id int default 0, password varchar(255) default \"000000\"");
	mdb.insert_table("tst", "12345, \"hshsh\"");
	mdb.insert_table("tst", "\"hshsh\"", "password");
	mdb.insert_table("tst", "12346", "id");
	mdb.update_table("tst", "password = 99999", "id = 12346");
	vector<vector<string>> ret = mdb.selectitem("tst", "*");
	for (auto temp : ret) {
		for (auto& str : temp)
			cout << str << " ";
		cout << endl;
	}
	mdb.delete_table("tst", "id = 0");
	ret = mdb.selectitem("tst", "*");
	for (auto temp : ret) {
		for (auto& str : temp)
			cout << str << " ";
		cout << endl;
	}
	mdb.query("*", "tst");
	mdb.delete_database("mydb");
	mdb.disconnect();
}