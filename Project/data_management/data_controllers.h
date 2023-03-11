// Data controller base classes

#pragma once

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mutex>
#include <string>


using std::string;


class MySQLBase
{
public:
    MySQLBase(string user, string password)
    {
        std::lock_guard<std::mutex> lk(mut);
        driver = sql::mysql::get_mysql_driver_instance();

        if (first_run){
            sql::Connection *con = driver->connect("tcp://127.0.0.1:3306", user, password);
            sql::Statement *stmt = con->createStatement();
            stmt->execute("CREATE DATABASE IF NOT EXISTS MPCS51410_proj");
            delete con;
            delete stmt;
            first_run = false;
        }
    }

protected:
    static std::mutex mut;
    static bool first_run;
    sql::mysql::MySQL_Driver *driver;
};

