// User object construction through component and prototype patterns

#pragma once
#include "account_data_objects.h"
#include "../admin_management/admin_process.h"
#include "../course_manipulation/course_manip_process.h"
#include "../registration/registration_process.h"

#include <memory>
#include <vector>



using std::unique_ptr;
using std::make_unique;


// Abstract class for user prototypes
class UserObject
{
public:
    virtual ~UserObject() = default;
    virtual unique_ptr<UserObject> clone(const User u);
};


// Variadic mixin template that creates user prototypes
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
class UserPrototypeFactory
{
public:
    static unique_ptr<UserObject> get_user_role(Roles role, User u);

private:
    UserPrototypeFactory() {}
};
