// Data objects interface for registration context


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
    string quarter;
    vector<string> days;
};

struct Course
{
    Course(string c_id, int i_id, string sum, vector<string> prereqs,
            bool consent, Schedule sched);

    ~Course() = default;

    Course(const Course& cpy);

    Course& operator=(const Course& cpy);

    // Public data members
    string course_id;
    int instructor_id;
    string summary;
    vector<string> prereqs;
    bool consent;
    unique_ptr<Schedule> schedule;
};

using CourseList = vector<unique_ptr<Course>>;


// Grade struct used in Transcript container below
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

    // Public data members
    unique_ptr<Course> course;
    string grade;
};
using Transcript = vector<unique_ptr<Grade>>;


// Course add/drop objects
enum RegResult { success, course_full, reg_closed, consent, pre_reqs, holds };
using RegAttempt = vector<RegResult>;

struct RegistrationData
{
    RegistrationData(User u, Course c, RegAttempt& r);

    ~RegistrationData() = default;

    RegistrationData(const RegistrationData& cpy);

    RegistrationData& operator=(const RegistrationData& cpy);

    void set_result(RegAttempt r) { *results = r; }

    // Public data members
    unique_ptr<User> user;
    unique_ptr<Course> course;
    unique_ptr<RegAttempt> results;
};


// Student holds data object
enum HoldTypes { CorseEvals, OutstandingTuition, OutstandingHealthReq, GPA };
using StudentHolds = vector<HoldTypes>;
