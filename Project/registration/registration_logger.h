// Logging functionality for registration context using observer pattern


#pragma once
#include "../identity_access/event_logger.h"

// Registration context log events
enum RegEvents { course_search,
                 add_course,
                 drop_course,
                 view_trans,
                 view_sched,
                 view_holds,
                 update_holds};


// Registration context log event observer
class RegLogObserver : public Observer<User>
{
private:
    EventLogger& logger;

public:
    RegLogObserver() : logger{EventLogger::instance()} {};
    void log_event(User user, int message_type);
};
