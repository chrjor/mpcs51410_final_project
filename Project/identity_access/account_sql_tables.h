// Create table commands for account identity and access context controller, do
// not include this header in other headers

#pragma once

#include <string>


static const std::string acc_users = R"(
    CREATE TABLE IF NOT EXISTS acc_users(
        cnetid VARCHAR(32),
        name VARCHAR(64),
        password VARCHAR(64),
        role TINYINT,
        PRIMARY KEY (cnetid)
    )
)";

