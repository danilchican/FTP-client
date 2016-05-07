#include "sqlite3.h"
class Database 
{
	sqlite3 *db;
	char *hostname;
	char *username;
	char *password;
public:
	Database();
	Database(char *params);
	bool getHostsList(); // get hosts list in database
	bool addNewHost(); // add new host to the database
	bool deleteHost(int id); // delete host by id from database
private:
	bool open(); // open database connection
	void close(); // close database connection
	bool exec(const char * qry); // exec sql query
	bool init(); // create database structure 
	void printErrorMessage(const char * errorMessage); // print error message
};