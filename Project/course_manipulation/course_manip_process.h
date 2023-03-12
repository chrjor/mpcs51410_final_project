// Course manipulation interface


#pragma once
#include <memory>

#include "course_manip_data_objects.h"


using std::unique_ptr;
using std::make_unique;


// Course manipulation context user role heirarchy
class CourseManipUser
{
public:
    CourseManipUser(User user) : user{make_unique<User>(user)} {}

    CourseManipUser(const CourseManipUser& cpy)
        : user{make_unique<User>(*cpy.user)} {}

    CourseManipUser& operator=(const CourseManipUser& cpy)
    {
        user = make_unique<User>(*cpy.user);
        return *this;
    }

    RosterAdapter<EnrolledStudent> view_roster(int course_id);

protected:
    unique_ptr<User> user;
};


class InstructorCourseUser : public CourseManipUser
{
public:
    InstructorCourseUser(User user) : CourseManipUser(user) {}

    CourseHistory get_prior_courses();

    void update_course_summary(string course_id, string summary);

    void assign_grade(string cnetid, string course_id, string grade);

    template<typename Recipients>
    void send_course_email(Recipients r, string message);
};


class AdminCourseUser : public CourseManipUser
{
public:
    AdminCourseUser(User user) : CourseManipUser(user) {}

    void update_course(CourseData course);
    void update_instructor();
};

