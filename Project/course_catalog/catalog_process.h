// Course catalog interface


#pragma once
#include <string>
#include <unordered_map>

#include "catalog_data_objects.h"
#include "catalog_data_controller.h"
#include "../identity_access/account_user_objects.h"


using std::string;


// Class adapter to qualify incoming course queries (command pattern) according
// to the role of the user making them. Returns data appropriate to the user's
// role.
class Catalog
{
public:
    CourseList course_search(Course course_query, Roles user_role);

private:
    std::unordered_map<string, unique_ptr<Course>> course_cache;
    unique_ptr<CatalogDataController> db_con;
};
