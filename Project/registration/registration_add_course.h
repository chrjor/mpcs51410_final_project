// Add course process interface


#pragma once
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "registration_data_objects.h"


using std::string;
using std::unique_ptr;
using std::make_unique;


// Chain of responsibility pattern for handling student add course process when
// initialized by student

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

    StudentAddProcessChain(const StudentAddProcessChain& cpy)
        : reg_attempt{make_unique<RegistrationData>(*cpy.reg_attempt)},
        next{ (cpy.next) ? make_unique<StudentAddProcessChain>(*cpy.next) : nullptr } {}

    StudentAddProcessChain& operator=(const StudentAddProcessChain& cpy)
    {
        reg_attempt = make_unique<RegistrationData>(*cpy.reg_attempt);
        next = (cpy.next) ? make_unique<StudentAddProcessChain>(*cpy.next) : nullptr;
        return *this;
    }

    StudentAddProcessChain(StudentAddProcessChain&& mv)
        : next{std::move(mv.next)},
        reg_attempt{std::move(mv.reg_attempt)} {}

    template<typename Handler>
    void set_next_handler(Handler next_handler)
    {
        if (next) {
            next->set_next_handler(next_handler);
        } else {
            next = make_unique<Handler>(next_handler);
        }
    }

    virtual void next_handle() { if (next) next->next_handle(); }
};


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
