// Event logging classes


#pragma once
#include <fstream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "account_data_objects.h"


using std::make_unique;
using std::string;
using std::unique_ptr;


// Log levels
enum log_context { course_manip, reg, admin };


// Observer template for log event
template<typename T>
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void log_event(T& source, string message, log_context level) = 0;
};


// Observable template for user logging
template<typename T>
class Observable
{
public:
    void log_event(T& observed, string message, log_context level)
    {
        std::lock_guard<std::mutex> loc(mtx);
        for (auto observer : observers) {
            observer->log_event(observed, message, level);
        }
    }

    void add_observer(unique_ptr<Observer<T>> observer)
    {
        std::lock_guard<std::mutex> loc(mtx);
        observers.push_back(make_unique<Observer<T>>(*observer));
    }

private:
    std::vector<unique_ptr<Observer<T>>> observers;
    std::mutex mtx;
};


// Event logging object
class EventLogger
{
public:
    // Singleton Pattern using static instance local to class
    static EventLogger& instance()
    {
        static EventLogger *instance = new EventLogger();
        return *instance;
    }

    // Write method
    void write_info(string message)
    {
        if (log_file) log_file << "INFO: " << message << std::endl;
    }

    void write_warn(string message)
    {
        if (log_file) log_file << "WARNING: " << message << std::endl;
    }

    void write_err(string message)
    {
        if (log_file) log_file << "ERROR :" << message << std::endl;
    }

    // Create new log
    void new_log()
    {
        log_file.close();
        std::remove("log_file.text");
        log_file.open("log_file.txt");
    }

private:
    EventLogger() { log_file.open("log_file.txt"); }
    ~EventLogger() { log_file.close(); }

    std::ofstream log_file;
};



// Course manipulation context log event observer
class CourseManipLogObserver : public Observer<User>
{
private:
    EventLogger& logger;

public:
    CourseManipLogObserver() : logger{EventLogger::instance()} {};

    void log_event(User& user, string message_type, log_context level)
    {
        if (level != log_context::course_manip) return;
        if (message_type == "test") {
            logger.write_warn(message_type);
        }
    }
};


// Registration context log event observer
class RegLogObserver : public Observer<User>
{
private:
    EventLogger& logger;

public:
    RegLogObserver() : logger{EventLogger::instance()} {};

    void log_event(User& user, string message_type, log_context level)
    {
        if (level != log_context::reg) return;
        if (message_type == "test") {
            logger.write_err(message_type);
        }
    }
};


// Admin context log event observer
class AdminLogObserver : public Observer<User>
{
private:
    EventLogger& logger;

public:
    AdminLogObserver() : logger{EventLogger::instance()} {};

    void log_event(User& user, string message_type, log_context level)
    {
        if (level != log_context::admin) return;
        if (message_type == "test") {
            logger.write_info(message_type);
        }
    }
};



