// User object construction through component and prototype patterns


#include "account_user_objects.h"


unique_ptr<UserObject> UserPrototypeFactory::get_user_role(user_role role, User u)
{
    if (!prototypes[role]) {
        User empty_usr;
        switch (role) {
            case user_role::Instructor:
                using InstrRole = UserRole<InstructorRegUser, InstructorCourseUser>;
                prototypes.at(user_role::Instructor) = make_unique<InstrRole>(empty_usr);
                break;
            case user_role::TA:
                using TARole = UserRole<StudentRegUser, InstructorCourseUser>;
                prototypes.at(user_role::TA) = make_unique<TARole>(empty_usr);
                break;
            case user_role::Student:
                using StudRole = UserRole<StudentRegUser>;
                prototypes.at(user_role::Student) = make_unique<StudRole>(empty_usr);
                break;
            case user_role::Admin:
                using AdminRole = UserRole<AdminUser, AdminRegUser, AdminCourseUser>;
                prototypes.at(user_role::Admin) = make_unique<AdminRole>(empty_usr);
                break;
        }
    }
    return prototypes[role]->clone(u);
}

vector<unique_ptr<UserObject>> UserPrototypeFactory::prototypes(4);
