// Data objects functionality for course catalog


#include "catalog_data_objects.h"
#include "../identity_access/account_user_objects.h"

#include <memory>


using std::make_unique;


// AdminState class functionality
bool AdminState::add_student(string cnet_id)
{
    // Allow adding any current student
    return true;
}


bool AdminState::drop_student(string cnet_id)
{
    // Allow dropping any current student
    return true;
}


// StudentState class functionality
bool StudentState::add_student(string cnet_id)
{
    // Only add if course not at capacity and is open to modify
    return true;
}


bool StudentState::drop_student(string cnet_id)
{
    // Only drop if course is open to modify
    return true;
}


// Main Course class functionality
Course::Course(string c_id, int i_id, string sum, vector<string> prereqs,
        bool consent, Schedule sched)
    : course_id{c_id}, instructor_id{i_id}, summary{sum}, prereqs{prereqs},
    consent{consent}, schedule{make_unique<Schedule>(std::move(sched))} {}


Course::Course(const Course& cpy)
    : course_id{cpy.course_id}, instructor_id{cpy.instructor_id},
    summary{cpy.summary}, prereqs{cpy.prereqs}, consent{cpy.consent},
    schedule{std::make_unique<Schedule>(*cpy.schedule)} {}


Course& Course::operator=(const Course& cpy)
{
    course_id = cpy.course_id;
    instructor_id = cpy.instructor_id;
    summary = cpy.summary;
    prereqs = cpy.prereqs;
    consent = cpy.consent;
    schedule = std::make_unique<Schedule>(*cpy.schedule);
    return *this;
}


template<>
void Course::clone_new_state<Roles>(Roles role)
{
    // Change state depending on role of user accessing this course object
    if (!state) {

        if (role == Roles::Student) {
            set_state(make_unique<StudentState>());

        } else if (role == Roles::Instructor || role == Roles::Admin) {
            set_state(make_unique<AdminState>());
        }
    }
}
