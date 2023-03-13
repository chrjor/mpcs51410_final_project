add_subdirectory(admin_management)
add_subdirectory(data_management)
add_subdirectory(course_catalog)
add_subdirectory(course_manipulation)
add_subdirectory(identity_access)
add_subdirectory(registration)

add_executable(program main.cpp)
target_link_libraries(program PRIVATE
    AdminManagement
    CourseCatalog
    CourseManipulation
    DataController
    IdentityAccess
    Registration
)
