#include "sqlite3.h"
class Database 
{
	sqlite3 *db;
	char *port;
	char *hostname;
	char *username;
	char *password;
public:
	Database();
	Database(char *params);
	Database(char *host_id, bool find_by_id);
	bool getHostsList(); // get hosts list in database
	bool addNewHost(); // add new host to the database
	bool deleteHost(int id); // delete host by id from database
	bool hasHost(); // check if has host selected by id
	const char * _hostname();
	const char * _port();
	const char * _username();
	const char * _password();
private:
	bool open(); // open database connection
	void close(); // close database connection
	bool exec(const char * qry); // exec sql query
	bool init(); // create database structure 
	void printErrorMessage(const char * errorMessage); // print error message
};