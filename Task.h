#ifndef TASK_H
#define TASK_H

#include <string>
#include "Date.h"
#include "Priority.h"

class Task {
public:
    std::string description;
    std::string category;
    bool completed;
    Priority priority;
    Date dueDate;

    Task(const std::string& desc, const std::string& cat = "General",
        Priority p = Priority::MEDIUM, const Date& date = Date());
};

#endif