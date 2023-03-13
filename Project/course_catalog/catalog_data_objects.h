// Course catalog data objects


#pragma once
#include <memory>
#include <string>
#include <vector>


using std::string;
using std::vector;
using std::unique_ptr;


// Course state abstract class
class CourseState
{
public:
    virtual ~CourseState() = default;
    virtual bool add_student(string cnet_id) = 0;
    virtual bool drop_student(string cnet_id) = 0;
};


// Static course state for Instructors and Admins
class AdminState : public CourseState
{
public:
    bool add_student(string cnet_id) override;
    bool drop_student(string cnet_id) override;
};


// Static course state for students
class StudentState : public CourseState
{
public:
    bool add_student(string cnet_id) override;
    bool drop_student(string cnet_id) override;
};


// Main Course class
class Course
{
public:
    Course(string c_id, int i_id, string sum, vector<string> prereqs,
            bool consent, class Schedule sched);

    ~Course() = default;

    Course(const Course& cpy);

    Course& operator=(const Course& cpy);

    template<typename Roles>
    void clone_new_state(Roles role);

    bool add_student(string cnet_id) { return state->add_student(cnet_id); }

    bool drop_student(string cnet_id) { return state->drop_student(cnet_id); }

    // Public data members
    string course_id;
    int instructor_id;
    string summary;
    vector<string> prereqs;
    bool consent;
    unique_ptr<Schedule> schedule;

private:
    unique_ptr<CourseState> state {nullptr};
    void set_state(unique_ptr<CourseState> state);
    void update_course(Course course);
};


// Course container
using CourseList = vector<unique_ptr<Course>>;


// Schedule object that holds course schedule
class Schedule
{
public:
    string bldg;
    int start_time;
    int end_time;
    int year;
    string quarter;
    vector<string> days;
};
