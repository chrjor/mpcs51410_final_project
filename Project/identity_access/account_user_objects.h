// User object construction through component and prototype patterns

#pragma once
#include <memory>
#include <vector>

#include "../admin_management/admin_process.h"
#include "../course_manipulation/course_manip_process.h"
#include "../registration/registration_process.h"


using std::unique_ptr;
using std::make_unique;
using std::vector;


// Abstract class for user role prototypes
class UserObject
{
public:
    virtual ~UserObject() = default;
    virtual unique_ptr<UserObject> clone(const User u) = 0;
};


// Variadic mixin template for user role prototypes
template<typename... Roles>
class UserRole : public UserObject, public Roles...
{
public:
    UserRole(const User user) : Roles(user)... {}

    // Prototype clone
    unique_ptr<UserObject> clone(const User u) override
    {
        return make_unique<UserRole<Roles...>>(u);
    }
};


// Factory method for user role prototypes
enum user_role { Instructor, TA, Student, Admin };

class UserPrototypeFactory
{
public:
    unique_ptr<UserObject> get_user_role(user_role role, User u);

private:
    UserPrototypeFactory() {}
    static vector<unique_ptr<UserObject>> prototypes;
};
