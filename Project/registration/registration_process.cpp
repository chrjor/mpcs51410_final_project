// Registration implementation


#include "registration_process.h"


void DropCourseVisitor::visit_admin(RegistrationUser<AdminRegUser>& user, string cnetid,
        Course course)
{}


void DropCourseVisitor::visit_instructor(RegistrationUser<InstructorRegUser>& student, string cnetid,
        Course course)
{}


void DropCourseVisitor::visit_student(RegistrationUser<StudentRegUser>& student, string cnetid,
        Course course)
{}


void AddCourseVisitor::visit_admin(RegistrationUser<AdminRegUser>& user, string cnetid,
        Course course)
{}


void AddCourseVisitor::visit_instructor(RegistrationUser<InstructorRegUser>& student, string cnetid,
        Course course)
{}


void AddCourseVisitor::visit_student(RegistrationUser<StudentRegUser>& student, string cnetid,
        Course course)
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

