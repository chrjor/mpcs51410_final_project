// Logging interface for admin context using observer pattern


#pragma once
#include "../identity_access/event_logger.h"


// Admin context log events
enum AdminEvents { course_search,
                 view_holds,
                 update_holds};


// Admin context log event observer
class AdminLogObserver : public Observer<User>
{
private:
    EventLogger& logger;

public:
    AdminLogObserver() : logger{EventLogger::instance()} {};
    void log_event(User user, int message_type);
};
