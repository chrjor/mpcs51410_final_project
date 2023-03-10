#include <catch2/catch_test_macros.hpp>

#include <string>

#include "../Project/identity_access/account_login.h"


TEST_CASE("UserData returns user", "[UserData]") {
    UserData user_data;
    std::string cnetid = "christianj";
    User new_user = user_data.get_user(cnetid);

    REQUIRE(new_user.cnet_id == cnetid);
}
