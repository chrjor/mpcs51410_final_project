// Account login process


#pragma once
#include <memory>

#include "account_data_objects.h"
#include "account_data_controller.h"


using std::unique_ptr;


// Forward declaration of UserObject
class UserObject;


// Object decorator class for account database login_user() method
class AccountAccess
{
public:
    unique_ptr<UserObject> login();

private:
    unique_ptr<AccDataController> db_con;
};


// Admin account decorator class
class AdminAccAccess
{
public:
    bool add_account(const User& new_user);
    bool rem_account(const User& user);

private:
    unique_ptr<AccDataController> db_con;
};
