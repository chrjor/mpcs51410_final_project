// Administrative user processes


#pragma once
#include <memory>

using std::unique_ptr;
using std::make_unique;

#include "../identity_access/account_data_objects.h"


class AdminUser
{
public:
    AdminUser(User user) :  user{make_unique<User>(user)} {}
    void add_user(User user);
    void remove_user(User user);
    void update_bldg_info();

private:
    unique_ptr<User> user;
};
