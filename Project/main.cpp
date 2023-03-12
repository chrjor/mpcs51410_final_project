// Main program


#include "identity_access/account_login.h"

#include <string>
#include <memory>


// MySQL global variables
std::string const mysql_uname {"chrjor"};
std::string const mysql_upass {"p"};


using std::unique_ptr;


int main()
{
    AccountAccess user_login;
    unique_ptr<UserObject> user_interface = user_login.login();

    return 0;
}
