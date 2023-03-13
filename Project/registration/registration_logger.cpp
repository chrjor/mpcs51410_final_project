// Logging functionality for registration context

#include "registration_logger.h"

#include <iostream>
#include <sstream> // Using stringstream to avoid compilation issues with std::format
#include <string>


using std::string;


// Registration context log event observer method
void RegLogObserver::log_event(User user, int message_type)
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
            case RegEvents::view_trans:
                ost << "viewed transcript\n";
                break;
            case RegEvents::view_sched:
                ost << "viewed schedule\n";
                break;
            case RegEvents::view_holds:
                ost << "viewed_holds\n";
                break;
            case RegEvents::update_holds:
                ost << "updated student's hold status\n";
                break;
        }
        logger.write_reg_event(ost.str());
}
