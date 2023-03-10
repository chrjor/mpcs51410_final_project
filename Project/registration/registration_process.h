// Registration interface


#pragma once
#include <memory>

#include "registration_add_course.h"
#include "registration_data_objects.h"


using std::unique_ptr;
using std::make_unique;


template<typename UserType>
class RegistrationUser;

// Visitor abstract class
class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit_student(RegistrationUser<class StudentRegUser>& student,
            string cnetid, Course course) = 0;
    virtual void visit_admin(RegistrationUser<class AdminRegUser>& user,
            string cnetid, Course course) = 0;
    virtual void visit_instructor(RegistrationUser<class InstructorRegUser>& user,
            string cnetid, Course course) = 0;
};


// Visitor class for removing student from course
class DropCourseVisitor : public Visitor
{
public:
    void visit_admin(RegistrationUser<AdminRegUser>& user, string cnetid,
            Course course) override;
    void visit_instructor(RegistrationUser<InstructorRegUser>& student,
            string cnetid, Course course) override;
    void visit_student(RegistrationUser<StudentRegUser>& student, string cnetid,
            Course course) override;
};


// Visitor class for adding student to course
class AddCourseVisitor : public Visitor
{
public:
    void visit_admin(RegistrationUser<AdminRegUser>& user, string cnetid,
            Course course) override;
    void visit_instructor(RegistrationUser<InstructorRegUser>& student,
            string cnetid, Course course) override;
    void visit_student(RegistrationUser<StudentRegUser>& student, string cnetid,
            Course course) override;
};


// CRTP base class for user interface classes for Faculty, Students, and Admin
template<typename UserType>
class RegistrationUser
{
public:
    RegistrationUser(User user_data) : user{make_unique<User>(user_data)} {}
    virtual ~RegistrationUser() = default;

    RegistrationUser(const RegistrationUser<UserType>& cpy)
        : user{make_unique<User>(*cpy.user)} {}

    RegistrationUser& operator=(const RegistrationUser<UserType>& cpy)
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

    RegAttempt add_course(Course course)
    {
        static_cast<UserType>(this)->accept(AddCourseVisitor(), user->name, course);
        return results;
    }

    RegAttempt drop_course(Course course)
    {
        static_cast<UserType>(this)->accept(DropCourseVisitor(), user->name, course);
        return results;
    }

    unique_ptr<User> user;

    RegAttempt results;
};


// Visitable user interface classes for Faculty, Students, and Admin
class Visitable
{
public:
    virtual ~Visitable() = default;
    virtual void accept(Visitor visitor, string cnetid, Course course) = 0;
};


class InstructorRegUser : public RegistrationUser<InstructorRegUser>, public Visitable
{
public:
    void accept(Visitor visitor, string cnetid, Course course) override
    {
        visitor.visit_instructor(*this, cnetid, course);
    }
};


class StudentRegUser : public RegistrationUser<StudentRegUser>, public Visitable
{
public:
    Transcript view_transcript(string cnet_id);
    CourseList view_current_schedule(string cnet_id);
    void view_holds(string cnet_id);
    void accept(Visitor visitor, string cnetid, Course course) override
    {
        visitor.visit_student(*this, cnetid, course);
    }
};


class AdminRegUser : public RegistrationUser<AdminRegUser>, public Visitable
{
public:
    void update_student_record() {}
    void accept(Visitor visitor, string cnetid, Course course) override
    {
        visitor.visit_admin(*this, cnetid, course);
    }
};
