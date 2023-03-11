// Logging functionality for registration context using observer pattern


#pragma once
#include <sstream> // Using stringstream to avoid possible compilation issues with C++20 std::format
#include <string>

#include "../identity_access/event_logger.h"


using std::string;


// Registration context log events
enum RegEvents { course_search,
                 add_course,
                 drop_course};


// Registration context log event observer
class RegLogObserver : public Observer<User>
{
private:
    EventLogger& logger;

public:
    RegLogObserver() : logger{EventLogger::instance()} {};

    void log_event(User& user, int message_type)
    {
        std::ostringstream ost;
        ost << "Registration Event | User: " << user.name << " | ";
        switch (message_type) {
            case -1:
                ost << "test\n";
                break;
            case RegEvents::course_search:
                ost << "queried course catalog\n";
                break;
            case RegEvents::add_course:
                ost << "attmepted to register for course\n";
                break;
            case RegEvents::drop_course:
                ost << "attempted to drop course\n";
                break;
        }
        logger.write_reg_event(ost.str());
    }
};

