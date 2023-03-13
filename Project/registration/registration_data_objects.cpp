// Data objects functionality for registration context


#include "registration_data_objects.h"


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
