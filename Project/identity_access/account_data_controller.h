// Data controller for identity and access context

#pragma once

#include "mysql_connection.h"
#include "mysql_driver.h"

#include "account_data_objects.h"
#include "../data_management/data_controllers.h"

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include <string>


using std::string;
using std::unique_ptr;


class AccDataController : MySQLBase
{
public:
    AccDataController();
    ~AccDataController() noexcept
    {
        delete con;
        delete stmt;
    }

    unique_ptr<User> login_user(string cnet_id, string pass);

private:
    sql::Connection *con;
    sql::Statement *stmt;
};
