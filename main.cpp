#include"cbsdlreader.h"
#include "connect_database.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <string>
#include <list>
#include<cctype>
#include <winsock.h>
#include <mysql.h>
#pragma comment(lib,"libmySQL.lib")  //要加不然会编译出错
using namespace std;
void Process_database();
int main()
{
	/*ifstream inFile_BSDL("C:/Users/changeneversay/Desktop/边界扫描/BS文件/bsdl文件/SN74BCT8244A.bsdl");
	ostringstream temp;
	temp << inFile_BSDL.rdbuf();
	string BsdlFileContent = temp.str();
	CBsdlReader* d = new CBsdlReader;
	d->ProcessBsdlFile(BsdlFileContent);*/
	Process_database();
	//delete d;
	//d = nullptr;
	system("pause");
	return 0;
}