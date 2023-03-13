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
    MySQLBase();
    ~MySQLBase() = default;

protected:
    static std::mutex mut;
    static bool first_run;
    sql::mysql::MySQL_Driver *driver;
};
