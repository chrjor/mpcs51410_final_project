// Add course process implementation


#include "registration_add_course.h"


// StudentAddProcessChain functionality
StudentAddProcessChain::StudentAddProcessChain(const StudentAddProcessChain& cpy)
    : reg_attempt{make_unique<RegistrationData>(*cpy.reg_attempt)},
    next{ (cpy.next) ? make_unique<StudentAddProcessChain>(*cpy.next) : nullptr } {}


StudentAddProcessChain& StudentAddProcessChain::operator=(const StudentAddProcessChain& cpy)
    {
        reg_attempt = make_unique<RegistrationData>(*cpy.reg_attempt);
        next = (cpy.next) ? make_unique<StudentAddProcessChain>(*cpy.next) : nullptr;
        return *this;
    }


StudentAddProcessChain::StudentAddProcessChain(StudentAddProcessChain&& mv)
    : next{std::move(mv.next)}, reg_attempt{std::move(mv.reg_attempt)} {}


template<typename Handler>
void StudentAddProcessChain::set_next_handler(Handler next_handler)
{
    if (next) {
        next->set_next_handler(next_handler);
    } else {
        next = make_unique<Handler>(next_handler);
    }
}
