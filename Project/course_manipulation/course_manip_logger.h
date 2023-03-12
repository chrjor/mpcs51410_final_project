// Logging interface for course manipulation context using observer pattern


#pragma once

#include "../identity_access/event_logger.h"


// Log events
enum CourseManipEvents { course_search,
                         update_holds};


// Course manipulation context log event observer
class CourseManipLogObserver : public Observer<User>
{
private:
    EventLogger& logger;

public:
    CourseManipLogObserver() : logger{EventLogger::instance()} {}
    void log_event(User& user, int message_type);
};
