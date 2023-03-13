// Registration interface


#pragma once
#include <string>
#include <memory>

#include "../course_catalog/catalog_data_objects.h"
#include "registration_logger.h"
#include "registration_data_controller.h"
#include "registration_user_visitors.h"


using std::string;
using std::unique_ptr;
using std::make_unique;


// CRTP base class for Faculty, Students, and Admin registration users (with log observer)
template<typename UserType>
class RegistrationUser : public Observable<User>
{
public:
    RegistrationUser(User user_data)
        : user{make_unique<User>(user_data)},
        db_con{make_unique<RegDataController>()} {}

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
        Observable::log_event(*user, RegEvents::course_search);
        return new_list;
    }

    RegAttempt add_course(Course course)
    {
        static_cast<UserType>(this)->accept(AddCourseVisitor(), user->name, course);
        Observable::log_event(*user, RegEvents::add_course);
        return results;
    }

    RegAttempt drop_course(Course course)
    {
        static_cast<UserType>(this)->accept(DropCourseVisitor(), user->name, course);
        Observable::log_event(*user, RegEvents::drop_course);
        return results;
    }

    // Public data member
    RegAttempt results;

protected:
    unique_ptr<User> user;
    unique_ptr<RegDataController> db_con;
};


// Visitable derived classes for Faculty, Students, and Admin. These classes interface
// with the client through the web UI
class InstructorRegUser : public RegistrationUser<InstructorRegUser>, public Visitable
{
public:
    InstructorRegUser(User user) : RegistrationUser<InstructorRegUser>(user)
    {
        Observable::add_observer(make_unique<RegLogObserver>());
    }
protected:
    void accept(Visitor * visitor, string cnetid, Course course) override
    {
        visitor->visit_instructor(*this, cnetid, course);
    }
};


class AdminRegUser : public RegistrationUser<AdminRegUser>, public Visitable
{
public:
    AdminRegUser(User user) : RegistrationUser<AdminRegUser>(user)
    {
        Observable::add_observer(make_unique<RegLogObserver>());
    }

    void update_hold(string cnetid, HoldTypes hold);

protected:
    void accept(Visitor * visitor, string cnetid, Course course) override
    {
        visitor->visit_admin(*this, cnetid, course);
    }
};


class StudentRegUser : public RegistrationUser<StudentRegUser>, public Visitable
{
public:
    StudentRegUser(User user) : RegistrationUser<StudentRegUser>(user)
    {
        Observable::add_observer(make_unique<RegLogObserver>());
    }

    Transcript view_transcript(string cnet_id);
    CourseList view_current_schedule(string cnet_id);
    StudentHolds view_holds(string cnet_id);

protected:
    void accept(Visitor * visitor, string cnetid, Course course) override
    {
        visitor->visit_student(*this, cnetid, course);
    }
};
