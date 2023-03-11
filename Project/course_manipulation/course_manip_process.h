// Course manipulation interface

#pragma once
#include <memory>
#include <string>
#include <vector>

#include "../registration/registration_data_objects.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;


// Course roster objects
class EnrolledStudent
{
public:
    EnrolledStudent(const string n, const string cnet, const string course,
            const string g = "")
        : name{n}, cnetid{cnet}, course{course}, grade{g} {}

    ~EnrolledStudent() = default;

    EnrolledStudent(EnrolledStudent const& cpy)
        : name{cpy.name}, cnetid{cpy.cnetid}, grade{cpy.grade}, course{cpy.course}
    {}

    EnrolledStudent& operator=(const EnrolledStudent& cpy)
    {
        name = cpy.name;
        cnetid = cpy.cnetid;
        grade = cpy.grade;
        course = cpy.course;
        return *this;
    }

    bool operator==(const EnrolledStudent& comp)
    {
        return (name == comp.name && cnetid == comp.cnetid);
    }

    bool operator!=(const EnrolledStudent& comp)
    {
        return (name != comp.name || cnetid != comp.cnetid);
    }

    bool set_grade() { return true; }
    void send_email() {}

protected:
    string name;
    string cnetid;
    string grade;
    string course;
};


template<typename Student>
class Roster
{
public:
    using CourseStudents = vector<Student>;

    Roster(CourseStudents roster)
        : roster{roster}, num_students{roster.size()} {};

    ~Roster() = default;

    Roster(const Roster& cpy)
        : roster{cpy.roster}, num_students{cpy.roster.size()} {};

    Roster& operator=(const Roster& cpy)
    {
        roster = cpy.roster;
        num_students = cpy.roster.size();
        return *this;
    }

    Roster& operator++() { cur_counter++; return *this; }

    Roster operator++(int) { Roster old = *this; ++(*this); return old; }

    bool operator!=(const Roster& rhs_cmp) const
    {
        return (&roster[cur_counter] == &rhs_cmp[rhs_cmp.cur_counter]);
    }

    Student& operator[](int i) { return std::forward(roster[i]); }

    auto begin() const { return roster.begin(); }
    auto end() const { return roster.end(); }

    size_t size() { return num_students; }
    void append(const Student& student)
    {
        roster.push_back(student);
        num_students = roster.size();
    }

  void send_email() { for (auto& student : roster) student->send_email(); }

protected:
    CourseStudents roster {};
    int num_students {};
    int cur_counter {};
};


// Course manipulation objects
class CourseData
{
public:
    Course course_data;
    Roster<EnrolledStudent> roster;
};
using CourseHistory = vector<CourseData>;


// Role heirarchy
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

    Roster<EnrolledStudent> view_roster(int course_id);

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

