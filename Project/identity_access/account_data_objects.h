// Identity and Access data objects

#pragma once
#include <string>


using std::string;


enum Roles { Instructor, TA, Student, Admin };


struct User
{
    string cnet_id;
    string name;
    string password;
    Roles role;
};


class UserData
{
protected:
    bool add_account(const User&);
    bool rem_account(const User&);
public:
    User get_user(const string cnetid) const;
};
