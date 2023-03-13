// Add course process interface for a student attempt to add a course


#pragma once
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "registration_data_objects.h"


using std::string;
using std::unique_ptr;
using std::make_unique;


// Chain of responsibility base class
class StudentAddProcessChain
{
private:
    unique_ptr<StudentAddProcessChain> next{nullptr};

protected:
    unique_ptr<RegistrationData> reg_attempt;

public:
    StudentAddProcessChain() {}

    explicit StudentAddProcessChain(RegistrationData reg_data)
        : reg_attempt{make_unique<RegistrationData>(reg_data)} {}

    virtual ~StudentAddProcessChain() {}

    StudentAddProcessChain(const StudentAddProcessChain& cpy);

    StudentAddProcessChain& operator=(const StudentAddProcessChain& cpy);

    StudentAddProcessChain(StudentAddProcessChain&& mv);

    template<typename Handler>
    void set_next_handler(Handler next_handler);

    virtual void next_handle() { if (next) next->next_handle(); }
};


// Chain of responsibility handlers
class DetermineHolds : public StudentAddProcessChain
{
public:
    void next_handle() override
    {
        // Check if student has holds
    }
};


class DeterminePrereqs : public StudentAddProcessChain
{
public:
    void next_handle() override
    {
        // Check if student meets prerequisites
    }
};


class DetermineConsent : public StudentAddProcessChain
{
public:
    void next_handle() override
    {
        // Check if course requires instructor consent
    }
};


class AttemptAddCourse : public StudentAddProcessChain
{
public:
    void next_handle() override
    {
        // Check if course requires instructor consent
    }
};
