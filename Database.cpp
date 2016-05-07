#include "headers\Headers.h"
#include "headers\sqlite3.h"
#include <iomanip>

using namespace std;

Database::Database() : db(0)
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
		" `hostname` VARCHAR(80) NOT NULL ,"
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
	cout << "SQL: " << errorMessage << endl;
}
bool Database::getHostsList()
{
	if (!this->open()) {
		cout << DB_NOT_ACCESSABLE << endl;
		this->close();

		return false;
	}

	const char * SQL = "SELECT * FROM `accounts`",
				*data = "Callbacked";

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
		cout << "|   ID   ||      hostname      ||   username    |" << endl << endl;
		while (sqlite3_column_text(stmt, 0)) {
			for (int i = 0, step = 0; i < 3; i++) {
				step = (i != 0) ? 20 : 8;
				cout << "  " << setw(step) << left << sqlite3_column_text(stmt, i);
			}

			cout << endl;
			sqlite3_step(stmt);
		}
	}

	this->close();

	return true;
}