// Logging functionality for admin context


#include "admin_logger.h"

#include <iostream>
#include <sstream> // Using stringstream to avoid compilation issues with std::format
#include <string>


using std::string;


// Admin context log event observer method

void AdminLogObserver::log_event(User user, int message_type)
{
    std::ostringstream ost;
    ost << "Admin Event | User: " << user.name << " | ";
    switch (message_type) {
        case -1:
            ost << "test\n";
            break;
        case AdminEvents::course_search:
            ost << "queried course catalog\n";
            break;
        case AdminEvents::view_holds:
            ost << "viewed_holds\n";
            break;
        case AdminEvents::update_holds:
            ost << "updated student's hold status\n";
            break;
    }
    logger.write_reg_event(ost.str());
}
