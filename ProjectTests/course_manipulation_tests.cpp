// Unit tests for `course_manip_data_objects.h`


#include <catch2/catch_test_macros.hpp>
#include "../Project/course_manipulation/course_manip_data_objects.h"


TEST_CASE("EnrolledStudent copy by assignment and comparison works",
        "[EnrolledStudent]")
{
    EnrolledStudent Abe("Abe", "alincoln", "MPCS101", "A+");
    EnrolledStudent Abe_copy = Abe;

    REQUIRE(Abe == Abe_copy);
}


SCENARIO("Roster is an iterator", "[Roster]")
{
    GIVEN("An empty Roster object") {
        RosterAdapter<EnrolledStudent> roster;

        THEN("The size is zero") {
            REQUIRE(roster.size() == 0);
        }

        WHEN("append() method is called") {
            EnrolledStudent Abe("Abe", "alincoln", "MPCS101", "A+");
            roster.append(Abe);

            THEN("the roster size increases by 1") {
                REQUIRE(roster.size() == 1);
            }
        }

        WHEN("we want to set 3 students' grades") {

            EnrolledStudent Abe("Abe", "alincoln", "MPCS101", "A+");
            roster.append(Abe);
            EnrolledStudent Barack("Barack", "bobama", "MPCS101", "A+");
            roster.append(Barack);
            EnrolledStudent George("George", "gwash", "MPCS101", "A+");
            roster.append(George);

            THEN("we can use a range-for loop") {
                int grades_set = 0;
                for (auto student : roster) {
                    student.set_grade();
                    grades_set++;
                }

                REQUIRE(grades_set == 3);
            }
        }
    }
}
