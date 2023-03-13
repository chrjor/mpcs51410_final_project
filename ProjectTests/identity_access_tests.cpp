#include <catch2/catch_test_macros.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

#include "../Project/identity_access/account_login.h"
#include "../Project/identity_access/event_logger.h"
#include "../Project/registration/registration_logger.h"


TEST_CASE( "EventLogger is Singleton", "[EventLogger]") {
    EventLogger& logger1 = EventLogger::instance();
    EventLogger& logger2 = EventLogger::instance();
    REQUIRE(&logger1 == &logger2);
}

TEST_CASE( "EventLogger writes to log_file.txt", "[EventLogger]" ) {
    EventLogger& logger = EventLogger::instance();
    logger.write_reg_event("test");

    std::ifstream log("log_file.txt");
    std::string test;
    log >> test;

    REQUIRE(test == "test");

    log.close();
    std::ofstream log_wipe("log_file.txt");
    log_wipe.close();
}

TEST_CASE("Observers write to log", "[AdminObserver]") {
    EventLogger& logger = EventLogger::instance();
    User user;
    user.name = "C";
    std::vector<Observer<User> *> observers_vec {};
    observers_vec.push_back(new RegLogObserver());

    for (auto observer : observers_vec) {
        observer->log_event(user, RegEvents::add_course);
        std::fstream log("log_file.txt");
        std::string test;
        log >> test;

        REQUIRE(test == "Registration Event  User:");

        log.close();
        logger.new_log();
    }
    std::remove("log_file.txt");
}


