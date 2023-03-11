// Create table commands for Registration context controller, do not include this
// header in other headers

#pragma once

#include <string>


static const std::string reg_student_hist = R"(
    CREATE TABLE IF NOT EXISTS reg_student_hist(
        cnetid VARCHAR(32),
        courseid VARCHAR(32),
        year SMALLINT,
        quarter VARCHAR(6),
        grade VARCHAR(4),
        PRIMARY KEY (cnetid, courseid, year, quarter)
    )
)";

static const std::string reg_student_holds = R"(
    CREATE TABLE IF NOT EXISTS reg_student_holds(
        cnetid VARCHAR(32),
        hold_type VARCHAR(32)
        PRIMARY KEY (cnetid, hold_type)
    )
)";
