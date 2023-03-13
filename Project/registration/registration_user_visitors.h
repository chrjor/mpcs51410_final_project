// Visitor base classe interfaces for registration users

#pragma once
#include <string>

#include "../course_catalog/catalog_data_objects.h"


using std::string;


// Forward declaration of RegistrationUser
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


// Abstract base class for visitable user classes
class Visitable
{
public:
    virtual ~Visitable() = default;
protected:
    virtual void accept(Visitor * visitor, string cnetid, Course course) = 0;
};
