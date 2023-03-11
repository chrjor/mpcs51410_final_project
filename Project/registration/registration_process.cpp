// Registration implementation


#include "registration_process.h"
#include "registration_data_objects.h"
#include "registration_data_controller.h"
#include "registration_logger.h"


// Registration vistor functions
void DropCourseVisitor::visit_admin(RegistrationUser<AdminRegUser>& user,
        string cnetid, Course course)
{}


void DropCourseVisitor::visit_instructor(RegistrationUser<InstructorRegUser>& student,
        string cnetid, Course course)
{}


void DropCourseVisitor::visit_student(RegistrationUser<StudentRegUser>& student,
        string cnetid, Course course)
{}


void AddCourseVisitor::visit_admin(RegistrationUser<AdminRegUser>& user,
        string cnetid, Course course)
{}


void AddCourseVisitor::visit_instructor(RegistrationUser<InstructorRegUser>& student,
        string cnetid, Course course)
{}


void AddCourseVisitor::visit_student(RegistrationUser<StudentRegUser>& student,
        string cnetid, Course course)
{
    // Create registration data object
    RegistrationData reg_request(*student.user, course, student.results);

    // Set chain of responsibility handlers
    unique_ptr<StudentAddProcessChain> add_student_req;

    add_student_req = make_unique<StudentAddProcessChain>(reg_request);
    add_student_req->set_next_handler(DetermineHolds());
    add_student_req->set_next_handler(DeterminePrereqs());
    add_student_req->set_next_handler(DetermineConsent());
    add_student_req->set_next_handler(AttemptAddCourse());

    // Initiate request chain
    add_student_req->next_handle();

    // Set add course results
    student.results = *reg_request.results;
}


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
