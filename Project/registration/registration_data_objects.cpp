// Data objects functionality for registration context


#include "registration_data_objects.h"


// Course class functionality
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


// RegistrationData class functionality
RegistrationData::RegistrationData(User u, Course c, RegAttempt& r)
    : user{make_unique<User>(u)}, course{make_unique<Course>(c)},
    results{make_unique<RegAttempt>(std::move(r))} {}


RegistrationData::RegistrationData(const RegistrationData& cpy)
    : user{make_unique<User>(*cpy.user)}, course{make_unique<Course>(*cpy.course)},
    results{make_unique<RegAttempt>(*cpy.results)} {}


RegistrationData& RegistrationData::operator=(const RegistrationData& cpy)
{
    user = make_unique<User>(*cpy.user);
    course = make_unique<Course>(*cpy.course);
    results = make_unique<RegAttempt>(*cpy.results);
    return *this;
}
