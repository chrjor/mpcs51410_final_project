// Data objects used in registration context


#pragma once
#include <memory>
#include <string>
#include <vector>

#include "../identity_access/account_login.h"


using std::string;
using std::vector;
using std::make_unique;
using std::unique_ptr;


// Public course objects used by course search
struct Schedule
{
    string bldg;
    int start_time;
    int end_time;
    int year;
    int quarter;
    vector<string> days;
};

struct Course
{
    Course(string name, int c_id, int i_id, string sum, vector<string> prereqs,
            bool consent, Schedule sched)
        : name{name}, course_id{c_id}, instructor_id{i_id},
        summary{sum}, prereqs{prereqs}, consent{consent},
        schedule{make_unique<Schedule>(std::move(sched))}
    {};

    ~Course() = default;

    Course(const Course& cpy)
        : name{cpy.name}, course_id{cpy.course_id},
        instructor_id{cpy.instructor_id}, summary{cpy.summary},
        prereqs{cpy.prereqs}, consent{cpy.consent},
        schedule{std::make_unique<Schedule>(*cpy.schedule)} {}

    Course& operator=(const Course& cpy)
    {
        name = cpy.name;
        course_id = cpy.course_id;
        instructor_id = cpy.instructor_id;
        summary = cpy.summary;
        prereqs = cpy.prereqs;
        consent = cpy.consent;
        schedule = std::make_unique<Schedule>(*cpy.schedule);
        return *this;
    }

    string name;
    int course_id;
    int instructor_id;
    string summary;
    vector<string> prereqs;
    bool consent;

    unique_ptr<Schedule> schedule;
};

using CourseList = vector<Course>;


// Transcript struct used by students
struct Grade
{
    Grade(Course course, string grade)
        : course{make_unique<Course>(course)}, grade{grade} {};

    ~Grade() = default;

    Grade(const Grade& cpy)
        : course{make_unique<Course>(*cpy.course)}, grade{cpy.grade} {}

    Grade& operator=(const Grade& cpy)
    {
        course = make_unique<Course>(*cpy.course);
        grade = cpy.grade;
        return *this;
    }

    unique_ptr<Course> course;
    string grade;
};
using Transcript = vector<Grade>;


// Course add/drop objects
enum RegResults { success, course_full, reg_closed, consent, pre_reqs, holds };

struct RegistrationData
{
    RegistrationData(User user, Course course)
        : user{make_unique<User>(user)},
        course{make_unique<Course>(course)} {};

    ~RegistrationData() = default;

    RegistrationData(const RegistrationData& cpy)
        : user{std::make_unique<User>(*cpy.user)},
        course{std::make_unique<Course>(*cpy.course)},
        result{cpy.result} {}

    RegistrationData& operator=(const RegistrationData& cpy)
    {
        user = std::make_unique<User>(*cpy.user);
        course = std::make_unique<Course>(*cpy.course);
        result = cpy.result;
        return *this;
    }

    void set_result(RegResults r) { result = r; }

    unique_ptr<User> user;
    unique_ptr<Course> course;
    RegResults result;
};
