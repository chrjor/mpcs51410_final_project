#include <catch2/catch_test_macros.hpp>

#include <fstream>
#include <string>
#include <cstdio>

#include "../Project/identity_access/event_logger.cpp"
#include "../Project/identity_access/account_login.h"


TEST_CASE( "EventLogger is Singleton", "[EventLogger]") {
    EventLogger& logger1 = EventLogger::instance();
    EventLogger& logger2 = EventLogger::instance();
    REQUIRE(&logger1 == &logger2);
}

TEST_CASE( "EventLogger writes to log_file.txt", "[EventLogger]" ) {
    EventLogger& logger = EventLogger::instance();
    logger.write_to_log("test");

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
    std::vector<Observer<User> *> observers_vec {};
    observers_vec.push_back(new AdminObserver());
    observers_vec.push_back(new CourseManipObserver());
    observers_vec.push_back(new LoginObserver());
    observers_vec.push_back(new RegistrationObserver());

    for (auto observer : observers_vec) {
        observer->log_event(user, "test");
        std::fstream log("log_file.txt");
        std::string test;
        log >> test;

        REQUIRE(test == "test");

        log.close();
        logger.new_log();
    }

    std::remove("log_file.txt");
}


