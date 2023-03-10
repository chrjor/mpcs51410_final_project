// Identity and Access data objects

#pragma once
#include <string>

struct User
{
    std::string cnet_id;
    std::string name;
    std::string password;
    std::string role;
};


class UserData
{
protected:
    bool add_account(const User&);
    bool rem_account(const User&);
public:
    User get_user(const std::string cnetid) const;
};
