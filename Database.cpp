#include "headers\Headers.h"
#include "headers\sqlite3.h"
#include <iomanip>

using namespace std;

Database::Database() : db(0), hostname(NULL), port(NULL), username(NULL), password(NULL)
{
	bool created = (sqlite3_open(DB_NAME, &(this->db))) ? false : true;

	if (!created) {
		cout << "Cannot create/open database..." << endl;
	}
	else {
		this->init();
	}

	this->close();
}
Database::Database(char *host_id, bool find_by_id) : db(0), hostname(NULL), port(NULL), username(NULL), password(NULL)
{
	bool created = (sqlite3_open(DB_NAME, &(this->db))) ? false : true;

	if (!created) {
		cout << "Cannot create/open database..." << endl;
	}
	else {
		if (!this->init()) {
			cout << "Error init database..." << endl;
		}
		else {
			string SQL = "SELECT * FROM `accounts` WHERE id='" + string(host_id) + "'";
			const char  * data = 0;

			char *errMsg = 0;
			int stat = 0;

			sqlite3_stmt *stmt;

			sqlite3_prepare_v2(this->db, SQL.c_str(), -1, &stmt, NULL);
			stat = sqlite3_step(stmt);

			if (stat != SQLITE_DONE)
			{
				int errorCode = 0;
				if (errorCode = sqlite3_exec(this->db, SQL.c_str(), NULL, (void *)data, &errMsg) != SQLITE_OK) {
					this->printErrorMessage(errMsg);
					sqlite3_free(errMsg);
					this->close();

					return;
				}
			}

			if (stat == SQLITE_ROW) {
				sqlite3_column_text(stmt, 0);

				char *temp = (char *)sqlite3_column_text(stmt, 1);

				this->hostname = new char[strlen(temp) + 1];
				strcpy(this->hostname, temp);

				temp = (char *)sqlite3_column_text(stmt, 2);
				this->port = new char[strlen(temp) + 1];
				strcpy(this->port, temp);

				temp = (char *)sqlite3_column_text(stmt, 3);
				this->username = new char[strlen(temp) + 1];
				strcpy(this->username, temp);

				temp = (char *)sqlite3_column_text(stmt, 4);
				this->password = new char[strlen(temp) + 1];
				strcpy(this->password, temp);
			}
		}
	}

	this->close();
}
Database::Database(char *params) : db(0), hostname(NULL), port(NULL), username(NULL), password(NULL)
{
	bool created = (sqlite3_open(DB_NAME, &(this->db))) ? false : true;

	if (!created) {
		cout << "Cannot create/open database..." << endl;
	}
	else {
		if (!this->init()) {
			cout << "Error init database..." << endl;
		}
		else {
			char *commandLine = new char[strlen(params) + 1];
			strcpy_s(commandLine, strlen(params) + 1, params);

			char *pch = strtok(commandLine, ",");

			this->hostname = new char[strlen(pch) + 1];
			strcpy(hostname, pch);

			pch = strtok(NULL, ",");
			this->port = new char[strlen(pch) + 1];
			strcpy(port, pch);
			
			pch = strtok(NULL, ",");
			this->username = new char[strlen(pch) + 1];
			strcpy(username, pch);

			pch = strtok(NULL, ",");
			this->password = new char[strlen(pch) + 1];
			strcpy(password, pch);
		}
	}

	this->close();
}
bool Database::open()
{
	return (sqlite3_open(DB_NAME, &(this->db))) ? false : true;
}
void Database::close()
{
	sqlite3_close(this->db);
}
bool Database::init()
{
	const char * SQL = "CREATE TABLE IF NOT EXISTS `accounts` ("
		" `id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE ,"
		" `hostname` VARCHAR(80) NOT NULL UNIQUE ,"
		" `port` INTEGER NOT NULL ,"
		" `user` VARCHAR(80) NULL DEFAULT NULL ,"
		" `password` VARCHAR(80) NULL DEFAULT NULL )";

	return (this->exec(SQL)) ? true : false;
}
bool Database::exec(const char *qry)
{
	char *err = 0;

	if (sqlite3_exec(this->db, qry, 0, 0, &err) != SQLITE_OK) {
		this->printErrorMessage(err);
		sqlite3_free(err);

		return false;
	}

	return true;
}
void Database::printErrorMessage(const char *errorMessage)
{
	cout << "SQL error: " << errorMessage << endl;
}
bool Database::getHostsList()
{
	if (!this->open()) {
		cout << DB_NOT_ACCESSABLE << endl;
		this->close();

		return false;
	}

	const char * SQL = "SELECT * FROM `accounts`",
				*data = 0;

	char *errMsg = 0;
	int stat = 0;

	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(this->db, SQL, -1, &stmt, NULL);
	stat = sqlite3_step(stmt);

	if (stat != SQLITE_DONE)
	{
		int errorCode = 0;
		if (errorCode = sqlite3_exec(this->db, SQL, NULL, (void *)data, &errMsg) != SQLITE_OK) {
			this->printErrorMessage(errMsg);
			sqlite3_free(errMsg);
			this->close();

			return false;
		}
	}

	if (stat != SQLITE_ROW) {
		cout << "Haven't any hosts..." << endl;
	}
	else {
		cout << "Database of saved hosts: " << endl << endl;
		cout << "|   ID   ||      hostname      ||   port   ||   username    |" << endl << endl;

		while (sqlite3_column_text(stmt, 0)) {
			for (int i = 0, step = 0; i < 4; i++) {
				step = (i != 0 && i != 2) ? 20 : 9;
				cout << "  " << setw(step) << left << sqlite3_column_text(stmt, i);
			}

			cout << endl;
			sqlite3_step(stmt);
		}
	}

	this->close();

	return true;
}
bool Database::addNewHost()
{
	if (!this->open()) {
		cout << DB_NOT_ACCESSABLE << endl;
		this->close();

		return false;
	}

	string SQL = "INSERT INTO `accounts` (`hostname`, `port`, `user`, `password`) "
		"VALUES ('" + string(hostname) + "', '"  + string(port) + "', '" + string(username) + "', '" + string(password) + "')";

	int stat = 0; 
	const char *data = 0;

	char *errMsg = 0;

	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(this->db, SQL.c_str(), -1, &stmt, NULL);
	stat = sqlite3_step(stmt);

	if (stat != SQLITE_DONE)
	{
		int errorCode = 0;
		if (errorCode = sqlite3_exec(this->db, SQL.c_str(), NULL, (void *)data, &errMsg) != SQLITE_OK) {
			this->printErrorMessage(errMsg);
			sqlite3_free(errMsg);
			this->close();

			return false;
		}
	}

	this->close();

	return true;
}
bool Database::deleteHost(int id)
{
	if (!this->open()) {
		cout << DB_NOT_ACCESSABLE << endl;
		this->close();

		return false;
	}
	char number[10];
	itoa(id, number, 10);

	string SQL = "DELETE from `accounts` WHERE id='" + string(number) + "'";

	int stat = 0;
	const char *data = 0;

	char *errMsg = 0;

	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(this->db, SQL.c_str(), -1, &stmt, NULL);
	stat = sqlite3_step(stmt);

	if (sqlite3_changes(db) == 0) {
		cout << "\nNo hosts deleted. Cannot find host with id = " << id << "!" << endl;

		this->close();

		return false;
	}

	if (stat != SQLITE_DONE)
	{
		int errorCode = 0;
		if (errorCode = sqlite3_exec(this->db, SQL.c_str(), NULL, (void *)data, &errMsg) != SQLITE_OK) {
			this->printErrorMessage(errMsg);
			sqlite3_free(errMsg);
			this->close();

			return false;
		}
	}

	this->close();

	return true;
}
bool Database::hasHost()
{
	return (this->hostname != NULL) ? true : false;
}
const char * Database::_hostname()
{
	return this->hostname;
}
const char * Database::_port()
{
	return this->port;
}
const char * Database::_username()
{
	return this->username;
}
const char * Database::_password()
{
	return this->password;
}