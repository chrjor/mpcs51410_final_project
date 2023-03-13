add_library(TestSources OBJECT
    course_manipulation_tests.cpp)

add_executable(Tests identity_access_tests.cpp)
target_link_libraries(Tests PUBLIC TestSources CourseManipulation IdentityAccess Registration)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(Tests)
