// Data controller classes


#include "data_controllers.h"
#include "../mysql_login.h"


MySQLBase::MySQLBase()
{
    std::lock_guard<std::mutex> lk(mut);
    driver = sql::mysql::get_mysql_driver_instance();

    if (first_run){
        sql::Connection *con = driver->connect("tcp://127.0.0.1:3306", mysql_uname, mysql_upass);
        sql::Statement *stmt = con->createStatement();
        stmt->execute("CREATE DATABASE IF NOT EXISTS MPCS51410_proj");
        delete con;
        delete stmt;
        first_run = false;
    }
}

bool MySQLBase::first_run = true;
