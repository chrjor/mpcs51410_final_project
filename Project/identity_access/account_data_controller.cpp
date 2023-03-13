// Data controller for identity and access context


#include "account_data_controller.h"

// Keep these in this .cpp (avoid global variables)
#include "account_sql_tables.h"
#include "../mysql_login.h"

#include <string>


// RegDataController public methods
AccDataController::AccDataController() : MySQLBase()
{
    con = MySQLBase::driver->connect("tcp://127.0.0.1:3306", mysql_uname, mysql_upass);

    // Prepare Registration table if not created already
    stmt = con->createStatement();
    stmt->execute("USE MPCS51410_proj");
    stmt = con->createStatement();
    stmt->execute(acc_users);
}

