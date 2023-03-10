// Registration interface


#pragma once
#include <memory>

#include "registration_add_course.h"
#include "registration_data_objects.h"


using std::unique_ptr;
using std::make_unique;


// Visitor abstract classes
class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit_student(class StudentRegUser& student, string cnetid,
            Course course) = 0;
    virtual void visit_admin(class AdminRegUser& user, string cnetid,
            Course course) = 0;
    virtual void visit_instructor(class InstructorRegUser& user, string cnetid,
            Course course) = 0;
};


class Visitable
{
public:
    virtual ~Visitable() = default;
    virtual void accept(Visitor * visitor, string cnetid, Course course) = 0;
};


// User interface classes for Faculty, Students, and Admin
class InstructorRegUser : public Visitable
{
public:
    InstructorRegUser() {}

    void accept(Visitor * visitor, string cnetid, Course course)
    {
        visitor->visit_admin(*this, cnetid, course);
    }
};


class StudentRegUser : public Visitable
{
public:
    StudentRegUser() {}

    Transcript view_transcript(string cnet_id)
    {Transcript t; return t;}

    CourseList view_current_schedule(string cnet_id)
    {CourseList c; return c;}

    void view_restrictions(string cnet_id)
    {}

    void accept(Visitor * visitor, string cnetid, Course course)
    {
        visitor->visit_student(*this, cnetid, course);
    }
};


class AdminRegUser : public Visitable
{
public:
    AdminRegUser() {}

    void update_student_record() {}

    void accept(Visitor * visitor, string cnetid, Course course)
    {
        visitor->visit_admin(*this, cnetid, course);
    }
};


template<typename UserType>
class RegistrationUser : public UserType
{
public:
    RegistrationUser<UserType>(User user_data) : user{make_unique<User>(user_data)} {}
    virtual ~RegistrationUser<UserType>() = default;

    RegistrationUser<UserType>(const RegistrationUser<UserType>& cpy)
        : user{make_unique<User>(*cpy.user)} {}

    RegistrationUser<UserType>& operator=(const RegistrationUser<UserType>& cpy)
    {
        user = make_unique<User>(*cpy.user);
        return *this;
    }

    User get_user() { return *user; }

    CourseList course_search(Course search_params)
    {
        CourseList new_list;
        return new_list;
    }

protected:
    unique_ptr<User> user;
};


// Visitor classes for adding student to course, differentiated by person making the request
class AddCourseVisitor : public Visitor
{
public:
    RegResults result;

    void visit_admin(AdminRegUser& user, string cnetid,
            Course course) override
    {
        // faculty / admin add student to course
    }

    void visit_student(StudentRegUser& student, string cnetid,
            Course course) override
    {
        // Create registration data object
        RegistrationData reg_request(cnetid, course);

        // Set chain of responsibility handlers
        unique_ptr<StudentAddProcessChain> add_student_req;

        add_student_req = make_unique<StudentAddProcessChain>(reg_request);
        add_student_req->set_next_handler(DetermineHolds());
        add_student_req->set_next_handler(DeterminePrereqs());
        add_student_req->set_next_handler(DetermineConsent());
        add_student_req->set_next_handler(AttemptAddCourse());

        // Make request
        add_student_req->next_handle();

        result = reg_request.result;
    }

};


// Visitor classes for removing student from course, differentiated by person making the request
class DropCourseVisitor : public Visitor
{
public:
    void visit_admin(AdminRegUser& user, string cnetid, Course course) override
    {
        // faculty / admin drop student from course
    }

    void visit_student(StudentRegUser& student, string cnetid, Course course) override
    {
        // student drops course
    }

    string result {};
};
