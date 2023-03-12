// Course manipulation data objects
//
// Roster object: RosterAdapter<EnrolledStudent>
// Student object: EnrolledStudent
// Course object: CourseData
// Course history object: CourseHistory (vector<CourseData>)
//


#pragma once
#include <string>
#include <vector>

#include "../registration/registration_data_objects.h"


using std::string;
using std::vector;


// Object adaptor (for standard library vector container) serving as an iterable
// course roster. Implements composite email method for all students in
// the roster.
template<typename Student>
class RosterAdapter
{
public:
    using CourseStudents = vector<Student>;

    RosterAdapter(CourseStudents roster)
        : roster{roster}, num_students{roster.size()} {};
    ~RosterAdapter() = default;

    RosterAdapter(const RosterAdapter& cpy)
        : roster{cpy.roster}, num_students{cpy.roster.size()} {};
    RosterAdapter& operator=(const RosterAdapter& cpy)
    {
        roster = cpy.roster;
        num_students = cpy.roster.size();
        return *this;
    }

    RosterAdapter& operator++() { cur_counter++; return *this; }
    RosterAdapter operator++(int) { RosterAdapter old = *this; ++(*this); return old; }

    bool operator!=(const RosterAdapter& rhs_cmp) const
    {
        return (&roster[cur_counter] == &rhs_cmp[rhs_cmp.cur_counter]);
    }

    Student& operator[](int i) { return std::forward(roster[i]); }

    auto begin() const { return roster.begin(); }
    auto end() const { return roster.end(); }

    size_t size() { return num_students; }
    void append(const Student& student)
    {
        roster.push_back(student);
        num_students = roster.size();
    }

  void send_emails() { for (auto& student : roster) student->send_email(); }

protected:
    CourseStudents roster {};
    int num_students {};
    int cur_counter {};
};


// Student Roster objects
class EnrolledStudent
{
public:
    EnrolledStudent(const string n, const string cnet, const string course,
            const string g = "")
        : name{n}, cnetid{cnet}, course{course}, grade{g} {}

    ~EnrolledStudent() = default;

    EnrolledStudent(EnrolledStudent const& cpy)
        : name{cpy.name}, cnetid{cpy.cnetid}, grade{cpy.grade}, course{cpy.course}
    {}

    EnrolledStudent& operator=(const EnrolledStudent& cpy)
    {
        name = cpy.name;
        cnetid = cpy.cnetid;
        grade = cpy.grade;
        course = cpy.course;
        return *this;
    }

    bool operator==(const EnrolledStudent& comp)
    {
        return (name == comp.name && cnetid == comp.cnetid);
    }

    bool operator!=(const EnrolledStudent& comp)
    {
        return (name != comp.name || cnetid != comp.cnetid);
    }

    bool set_grade() { return true; }
    void send_email() {}

protected:
    string name;
    string cnetid;
    string grade;
    string course;
};


// Complete course data object that is built and passed to user
class CourseData
{
public:
    Course course_data;
    RosterAdapter<EnrolledStudent> roster;
};

using CourseHistory = vector<CourseData>;
