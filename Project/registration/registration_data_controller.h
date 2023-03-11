// Registration data controller


#pragma once

#include "mysql_connection.h"
#include "mysql_driver.h"

#include "registration_data_objects.h"
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


class RegDataController : MySQLBase
{
public:
    RegDataController(string user, string password);
    ~RegDataController() noexcept
    {
        delete con;
        delete stmt;
        delete trnscpt_stmt;
        delete holds_stmt;
    }

    Transcript get_course_hist(string cnet_id);
    StudentHolds get_holds(string cnet_id);
    void update_hold(string cnet_id, HoldTypes hold);
    void add_student(RegistrationData reg_data);
    void remove_student(RegistrationData reg_data);

private:
    sql::Connection *con;
    sql::Statement *stmt;
    static sql::PreparedStatement *trnscpt_stmt;
    static sql::PreparedStatement *holds_stmt;
};

