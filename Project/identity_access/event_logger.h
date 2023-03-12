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


// Observer template for log event
template<typename T>
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void log_event(T& source, int message) = 0;
};


// Observable template for user logging
template<typename T>
class Observable
{
public:
    void log_event(T& observed, int message)
    {
        std::lock_guard<std::mutex> loc(mtx);
        for (auto observer : observers) {
            observer->log_event(observed, message);
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
    void write_reg_event(string message)
    {
        if (log_file) log_file << message;
    }

    void write_course_event(string message)
    {
        if (log_file) log_file << message;
    }

    void write_admin_event(string message)
    {
        if (log_file) log_file << message;
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
