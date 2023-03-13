// Visitor base class implementation for registration users

#include "registration_user_visitors.h"
#include "registration_process.h"
#include "registration_data_objects.h"
#include "registration_add_course.h"


// Registration vistor functions
void DropCourseVisitor::visit_admin(RegistrationUser<AdminRegUser>& user,
        string cnetid, Course course)
{
    // Admin can drop any student from any course
}


void DropCourseVisitor::visit_instructor(RegistrationUser<InstructorRegUser>& student,
        string cnetid, Course course)
{
    // Instructors can only drop students from their own courses
}


void DropCourseVisitor::visit_student(RegistrationUser<StudentRegUser>& student,
        string cnetid, Course course)
{
    // Students can only drop themselves from courses within the quarter drop period
}


void AddCourseVisitor::visit_admin(RegistrationUser<AdminRegUser>& user,
        string cnetid, Course course)
{
    // Admin can add any student to any current course
}


void AddCourseVisitor::visit_instructor(RegistrationUser<InstructorRegUser>& student,
        string cnetid, Course course)
{
    // Instructors can add any student to any course they are currently teaching
}


void AddCourseVisitor::visit_student(RegistrationUser<StudentRegUser>& student,
        string cnetid, Course course)
{
    // Students can only add a course if they meet all requirements

    // Create registration data object
    RegistrationData reg_request(student.get_user(), course, student.results);

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

