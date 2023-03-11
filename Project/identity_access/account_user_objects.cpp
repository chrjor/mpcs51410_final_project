// User object construction through component and prototype patterns


#include "account_user_objects.h"
#include <memory>


unique_ptr<UserObject> UserPrototypeFactory::get_user_role(Roles role, User u)
{
    static vector<unique_ptr<UserObject>> prototypes;

    if (!prototypes[role]) {
        User empty_usr;
        switch (role) {
            case Roles::Instructor:
                using InstrRole = UserRole<InstructorRegUser, InstructorCourseUser>;
                prototypes.at(Roles::Instructor) = make_unique<InstrRole>(empty_usr);
                break;
            case Roles::TA:
                using TARole = UserRole<StudentRegUser, InstructorCourseUser>;
                prototypes.at(Roles::TA) = make_unique<TARole>(empty_usr);
                break;
            case Roles::Student:
                using StudRole = UserRole<StudentRegUser>;
                prototypes.at(Roles::Student) = make_unique<StudRole>(empty_usr);
                break;
            case Roles::Admin:
                using AdminRole = UserRole<AdminUser, AdminRegUser, AdminCourseUser>;
                prototypes.at(Roles::Admin) = make_unique<AdminRole>(empty_usr);
                break;
        }
    }
    return prototypes[role]->clone(u);
}


vector<unique_ptr<UserObject>> UserPrototypeFactory::prototypes(4);
