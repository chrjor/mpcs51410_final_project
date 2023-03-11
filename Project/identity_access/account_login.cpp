// Account login implementation


#include "account_login.h"
#include "account_user_objects.h"

#include <iostream>
#include <string>


using std::string;
using std::cout;
using std::cin;


// Account login
unique_ptr<UserObject> AccountAccess::login()
{
    unique_ptr<User> user_details;
    bool login_success = false;

    while (!login_success){
        string cnet_id{}, pass{};

        cout << "Please enter cnetid and password: \n(hint, username: abelincoln, pass: gobears)\n";
        cout << "username: ";
        cin >> cnet_id;
        cout << "pass: ";
        cin >> pass;

        user_details = db_con->login_user(cnet_id, pass);

        if (user_details->cnet_id == "") {
            login_success = true;
        } else {
            cout << "No success, please try again...\n";
        }
    }

    return UserPrototypeFactory::get_user_role(user_details->role, *user_details);
}


// UserData methods
bool AdminAccAccess::add_account(const User& new_user)
{
    return true;
}

bool AdminAccAccess::rem_account(const User& user)
{
    return true;
}

