// Logging functionality

#include "course_manip_logger.h"

#include <iostream>
#include <sstream> // Using stringstream to avoid compilation issues with std::format
#include <string>


using std::string;


// Log event observer method
void CourseManipLogObserver::log_event(User user, int message_type)
{
        std::ostringstream ost;
        ost << "Couse Manipulation Event | User: " << user.name << " | ";
        switch (message_type) {
            case -1:
                ost << "test\n";
                break;
            case CourseManipEvents::course_search:
                ost << "queried course catalog\n";
                break;
            case CourseManipEvents::update_holds:
                ost << "updated student's hold status\n";
                break;
        }
        logger.write_course_event(ost.str());
}
