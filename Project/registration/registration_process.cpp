// Registration implementation


#include "registration_process.h"
#include "registration_data_objects.h"
#include "registration_add_course.h"


// Student registration user methods
Transcript StudentRegUser::view_transcript(string cnet_id)
{
    Observable::log_event(*user, RegEvents::view_trans);
    return db_con->get_course_hist(cnet_id);
}


CourseList StudentRegUser::view_current_schedule(string cnet_id)
{
    Transcript hist = db_con->get_course_hist(cnet_id);
    CourseList cur_sched;

    for (auto& hist_item : hist) {
        if (hist_item->grade == "CUR") {
            cur_sched.emplace_back(std::move(hist_item->course));
        }
    }
    Observable::log_event(*user, RegEvents::view_sched);
    return cur_sched;
}


StudentHolds StudentRegUser::view_holds(string cnet_id)
{
    Observable::log_event(*user, RegEvents::view_holds);
    return db_con->get_holds(cnet_id);
}


// Admin registration user methods
void AdminRegUser::update_hold(string cnet_id, HoldTypes hold)
{
    db_con->update_hold(cnet_id, hold);
    Observable::log_event(*user, RegEvents::update_holds);
}
