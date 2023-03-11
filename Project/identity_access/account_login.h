// Account login process


#pragma once
#include <memory>

#include "account_data_objects.h"
#include "account_data_controller.h"


using std::unique_ptr;


class UserObject;


class AccountAccess
{
public:
    unique_ptr<UserObject> login();

private:
    unique_ptr<AccDataController> db_con;
};


// Admin account actions
class AdminAccAccess
{
public:
    bool add_account(const User& new_user);
    bool rem_account(const User& user);
};
