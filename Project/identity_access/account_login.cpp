// Account login implementation

#include "account_login.h"


// UserData methods
bool UserData::add_account(const User& new_user)
{
    return true;
}

bool UserData::rem_account(const User& user)
{
    return true;
}

User UserData::get_user(const std::string cnet_id) const
{
    User new_user;
    new_user.cnet_id = "christianj";
    return new_user;
}
