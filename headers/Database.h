#include "sqlite3.h"
class Database 
{
	sqlite3 *db;
public:
	Database() : db(0)
	{};
public:
	bool open(); // open database connection
	void close(); // close database connection
};