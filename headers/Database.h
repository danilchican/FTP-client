#include "sqlite3.h"
class Database 
{
	sqlite3 *db;
public:
	Database();
	bool getHostsList(); // get hosts list in database
private:
	bool open(); // open database connection
	void close(); // close database connection
	bool exec(const char * qry); // exec sql query
	bool init(); // create database structure 
	void printErrorMessage(const char * errorMessage); // print error message
};