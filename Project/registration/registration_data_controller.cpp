// Registration data control


#include "registration_data_controller.h"

// Keep these in this .cpp (avoid global variables)
#include "registration_sql_tables.h"
#include "../mysql_login.h"


// RegDataController static initializations
sql::PreparedStatement *RegDataController::trnscpt_stmt = nullptr;
sql::PreparedStatement *RegDataController::holds_stmt = nullptr;


// RegDataController public methods
RegDataController::RegDataController() : MySQLBase()
{
    con = MySQLBase::driver->connect("tcp://127.0.0.1:3306", mysql_uname, mysql_upass);

    // Prepare Registration table if not created already
    stmt = con->createStatement();
    stmt->execute("USE MPCS51410_proj");
    stmt = con->createStatement();
    stmt->execute(reg_student_hist);
    stmt = con->createStatement();
    stmt->execute(reg_student_holds);
}


Transcript RegDataController::get_course_hist(string cnet_id)
{
    if (!trnscpt_stmt) {
        trnscpt_stmt = con->prepareStatement(R"(
            "SELECT cnetid, courseid, year, quarter, grade
            FROM reg_student_hist
            WHERE cnetid = ?"
        )");
    }

    trnscpt_stmt->setString(1, cnet_id);

    std::unique_ptr<sql::ResultSet> res;
    res.reset(trnscpt_stmt->executeQuery());

    Transcript t {};
    while (res->next()) {
        Schedule s;
        s.year = res->getInt("year");
        s.quarter = res->getString("quarter");
        Course c(res->getString("courseid"), 0, "", {}, false, s);
        Grade g(c, res->getString("grade"));
        t.emplace_back(make_unique<Grade>(g));
    }

    return t;
}


StudentHolds RegDataController::get_holds(string cnet_id)
{
    if (!holds_stmt) {
        holds_stmt = con->prepareStatement(R"(
            "SELECT cnetid, hold_type
             FROM reg_student_holds
             WHERE cnetid = ?
            "
        )");
    }

    holds_stmt->setString(1, cnet_id);

    std::unique_ptr<sql::ResultSet> res;
    res.reset(trnscpt_stmt->executeQuery());

    StudentHolds holds {};
    while (res->next()) {
        holds.push_back(HoldTypes(res->getInt("hold_type")));
    }

    return holds;
}


void RegDataController::update_hold(string cnet_id, HoldTypes hold)
{
    sql::PreparedStatement *new_hold;

    new_hold = con->prepareStatement("INSERT INTO reg_student_holds(cnetid, hold_type) VALUES (?, ?)");
    new_hold->setString(1, cnet_id);
    new_hold->setInt(1, hold);
}
