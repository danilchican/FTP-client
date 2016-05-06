#include "headers\Headers.h"
#include "headers\sqlite3.h"

using namespace std;

bool Database::open()
{
	return (sqlite3_open(DB_NAME, &(this->db))) ? false : true;
}
void Database::close()
{
	sqlite3_close(this->db);
}