// Data objects interface for registration context


#pragma once
#include <memory>
#include <string>
#include <vector>

#include "../identity_access/account_login.h"
#include "../course_catalog/catalog_data_objects.h"


using std::string;
using std::vector;
using std::make_unique;
using std::unique_ptr;


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
