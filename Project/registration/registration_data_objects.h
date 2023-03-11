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
    string quarter;
    vector<string> days;
};

struct Course
{
    Course(string c_id, int i_id, string sum, vector<string> prereqs,
            bool consent, Schedule sched)
        : course_id{c_id}, instructor_id{i_id},
        summary{sum}, prereqs{prereqs}, consent{consent},
        schedule{make_unique<Schedule>(std::move(sched))}
    {};

    ~Course() = default;

    Course(const Course& cpy)
        : course_id{cpy.course_id}, instructor_id{cpy.instructor_id},
        summary{cpy.summary}, prereqs{cpy.prereqs}, consent{cpy.consent},
        schedule{std::make_unique<Schedule>(*cpy.schedule)} {}

    Course& operator=(const Course& cpy)
    {
        course_id = cpy.course_id;
        instructor_id = cpy.instructor_id;
        summary = cpy.summary;
        prereqs = cpy.prereqs;
        consent = cpy.consent;
        schedule = std::make_unique<Schedule>(*cpy.schedule);
        return *this;
    }

    string course_id;
    int instructor_id;
    string summary;
    vector<string> prereqs;
    bool consent;

    unique_ptr<Schedule> schedule;
};

using CourseList = vector<unique_ptr<Course>>;


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
using Transcript = vector<unique_ptr<Grade>>;


// Course add/drop objects
enum RegResult { success, course_full, reg_closed, consent, pre_reqs, holds };

using RegAttempt = vector<RegResult>;

struct RegistrationData
{
    RegistrationData(User u, Course c, RegAttempt& r)
        : user{make_unique<User>(u)},
        course{make_unique<Course>(c)},
        results{make_unique<RegAttempt>(std::move(r))} {}

    ~RegistrationData() = default;

    RegistrationData(const RegistrationData& cpy)
        : user{make_unique<User>(*cpy.user)},
        course{make_unique<Course>(*cpy.course)},
        results{make_unique<RegAttempt>(*cpy.results)} {}

    RegistrationData& operator=(const RegistrationData& cpy)
    {
        user = make_unique<User>(*cpy.user);
        course = make_unique<Course>(*cpy.course);
        results = make_unique<RegAttempt>(*cpy.results);
        return *this;
    }

    void set_result(RegAttempt r) { *results = r; }

    unique_ptr<User> user;
    unique_ptr<Course> course;
    unique_ptr<RegAttempt> results;
};


// Student holds data object
enum HoldTypes { CorseEvals, OutstandingTuition, OutstandingHealthReq, GPA };

using StudentHolds = vector<HoldTypes>;
